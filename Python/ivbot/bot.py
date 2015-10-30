__author__ = 'ivanychev'

"""
        This is a Telegram bot that is capable of converting latex formulas to
        .png via using pdflatex + pdfcrop + convert (by imagemagik)

        Now these commands are supported:

            /hello
            /latex <formula>
            /help

        Version 1.0

        Author: Sergey Ivanychev
"""

import requests
import time
import subprocess
import os
import sys


class formula_bot:

    __BOT_TOKEN = "155371517:AAFAdqcPrtj5Zf1w0bckV3usTKIJo7Eoz5E"
    __INTERVAL  = 3
    __ADMIN_ID  = 40271726
    __BOT_NAME  = "@formula_bot"
    __LOG_NAME  = "log.txt"
    __REQUESTS_FILE = "requests.txt"
    __LOG_ID    = None
    __HELP_FILE = "help.txt"
    __PIC_FILE  = "pic.png"
    __URL       = "https://api.telegram.org/bot"
    __URL_COMMANDS = {"get_updates":  '/getUpdates',\
                      "send_message": '/sendMessage',\
                      "send_photo":   '/sendPhoto'}
    __COMMANDS     = {"help":  ["/help"],\
                      "hello": ["/hello"],\
                      "latex": ["/latex"]}
    __LAST_UPDATE = 0

    """
    offset 	    Integer 	Optional 	Identifier of the first update to be returned. Must be greater by one than
                                        the highest among the identifiers of previously received updates.
                                        By default, updates starting with the earliest unconfirmed update are returned.
                                        An update is considered confirmed as soon as getUpdates is called with an offset
                                        higher than its update_id.
    limit 	    Integer 	Optional 	Limits the number of updates to be retrieved values between 1—10
                                        Defaults to 100
    timeout 	Integer 	Optional 	Timeout in seconds for long polling. Defaults to 0, i.e. usual short polling
    """

    def __init_commands(self):
        self.__COMMANDS["help"].append(self.__command_help)
        self.__COMMANDS["hello"].append(self.__command_hello)
        self.__COMMANDS["latex"].append(self.__command_latex)
        return True

    def __init_routine(self):
        pass
        self.__LOG_ID = open(self.__LOG_NAME, "a")
        print(type(self.__LOG_ID))

    def __init__(self, update_interval = 1):
        self.__init_commands()
        self.__init_routine()
        self.__INTERVAL = update_interval

    def __get_info(self):
        ret = ""
        ret += "Telegram bot server\n"
        ret += "Bot name:       %s\n"        % self.__BOT_NAME
        ret += "Bot token:      %s\n"        % self.__BOT_TOKEN
        ret += "Last update id: %s\n"        % self.__LAST_UPDATE
        ret += "Admin id:       %s\n"        % self.__ADMIN_ID
        return ret

    def __repr__(self):
        return self.__get_info()

    def __str__(self):
        return self.__get_info()

    def __url_cmd(self, command):
        return self.__URL + self.__BOT_TOKEN + self.__URL_COMMANDS[command]

    def log_event(self, string, data):
        out = "[TIME %s] \n%s\n" % (time.ctime(), string)
        out += self.__data2str(data)
        self.log_text(out)

    def log_text(self, string):
        print(string)
        self.__log_to_file(string)

    def __log_to_file(self, string):
        self.__LOG_ID.write(string)
        self.__LOG_ID.flush()
        return True

    def __data2str(self, data):
        string = ""
        string += "[USER  ]: %s\n"  % data["username"]
        string += "[CHATID]: %s\n"  % data["chat_id"]
        string += "[UPDTID]: %s\n"  % data["update_id"]
        string += "[TEXT]  :\n====\n%s\n====\n" % data["text"]
        return string



    def send_text(self, string, in_data):
        user_id = in_data["chat_id"]
        self.log_event('Sending to %s: %s' % (user_id, string), in_data)
        out_data = {'chat_id': user_id, 'text': string}
        response = requests.post(self.__url_cmd("send_message"), data=out_data)
        if not response.status_code == 200:
            return False
        return response.json()["ok"]

    def send_pic(self, filename, data):
        files = {'photo': open(filename, 'rb')}
        request = requests.post(self.__url_cmd('send_photo'), data=data, files=files)
        return request.json()['ok']

    def __get_command(self, string):
        token = string.lstrip().split()[0]
        for key, value in self.__COMMANDS.items():
            try:
                if token == value[0]:
                    return key
            except IndexError:
                pass
        return False

    def __command_help(self, data):
        self.log_event("Help requested", data)
        try:
            f = open(self.__HELP_FILE)
            help_msg = f.read()
            f.close()
        except:
            help_msg = "Help is not working"
        return self.send_text(help_msg, data["chat_id"])

    def __command_hello(self, data):
        self.log_event("Handshake with %s" % data["username"], data)
        return self.send_text("Hello, %s" % data["username"], data)

    def __command_latex(self, data):
        self.log_event("LaTeX requested", data)
        expr = data["text"].lstrip()
        expr = expr[len(self.__COMMANDS["latex"][0]):]

        if expr.lstrip() == "":
            self.send_text("You forgot to type formula after command", data["chat_id"])
            self.log_text("! User didn't type a formula\n")
            return True
        subprocess.call(['latexit', expr])
        if not os.path.exists(self.__PIC_FILE):
            self.send_text("Failed to compile formula. See example in /help", data["chat_id"])
            self.log_text("! User mistyped formula:\n" + expr)
            return False
        ret = self.send_pic(self.__PIC_FILE, data)
        if ret == False:
            self.send_text("Failed to send picture", data["chat_id"])
            self.log_text("! Send pic failed\n")
            return False
        os.remove(self.__PIC_FILE)
        self.log_text("Success\n")
        return True

    def run_command(self, data):
        command = self.__get_command(data["text"])
        if not command:
            return False
        self.__exec_command(data, command)

    def __exec_command(self, data, command):
        return self.__COMMANDS[command][1](data)


    def __get_name(self, update):
        try:
            for x in ['first_name', 'username', 'last_name']:
                ret = update['message']['chat']['username']
                return ret
        except KeyError:
            return "Stranger without @username and both names"


    def check_updates(self):
        data = {'offset': self.__LAST_UPDATE + 1, 'limit': 5, 'timeout': 0}
        try:
            response = requests.post(self.__url_cmd("get_updates"), data = data)
        except:
            self.log_text('Error getting updates')
            return False

        if not response.status_code == 200:
            return False
        print(response.raw)
        response_json = response.json()
        if not response_json["ok"]:
            return False

        for update in response_json["result"]:
            self.__LAST_UPDATE = update['update_id']

            if 'message' not in update or 'text' not in update['message']:
                self.log_text('Unknown update: %s' % update)
                continue

            user_id   = update['message']['chat']['id']

            user_name = self.__get_name(update)
            # if user_id != self.__ADMIN_ID:
            #     self.send_text("You're not autorized to use me!", user_id)
            #     self.log_event('Unautorized: %s' % update)
            #     continue

            message = update['message']['text']
            parameters = {"update_id":self.__LAST_UPDATE,  \
                          "username": user_name,\
                          "chat_id":  user_id,  \
                          "text":     message}
            self.log_event("Message received", parameters)
            self.run_command(parameters)

    def run(self):
        while True:
            try:
                ret = self.check_updates()
                time.sleep(self.__INTERVAL)
            except KeyboardInterrupt:
                self.log_text("Interrupted by keyboard")
                break
