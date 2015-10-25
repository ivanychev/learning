__author__ = 'ivanychev'

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
    limit 	    Integer 	Optional 	Limits the number of updates to be retrieved. Values between 1—100 are accepted.
                                        Defaults to 100
    timeout 	Integer 	Optional 	Timeout in seconds for long polling. Defaults to 0, i.e. usual short polling
    """
    def __init_commands(self):
        self.__COMMANDS["help"].append(self.__command_help)
        self.__COMMANDS["hello"].append(self.__command_hello)
        self.__COMMANDS["latex"].append(self.__command_latex)
        return True

    def __init__(self):
        self.__init_commands()
        pass

    def __init__(self, update_interval):
        self.__init_commands()
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

    def log_event(self, string):
        print("[%s] %s" % (time.ctime(), string))

    def send_text(self, string, user_id):
        self.log_event('Sending to %s: %s' % (user_id, string))
        data = {'chat_id': user_id, 'text': string}
        response = requests.post(self.__url_cmd("send_message"), data=data)
        if not response.status_code == 200:
            return False
        return response.json()["ok"]

    def send_pic(self, filename, data):
        files = {'photo': open(filename, 'rb')}
        request = requests.post(self.__url_cmd('send_photo'), data=data, files=files) # Отправка фото
        return request.json()['ok'] # Возврат True или False, полученного из ответа сервера, в зависимости от результата

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
        try:
            f = open(self.__HELP_FILE)
            help_msg = f.read()
            f.close()
        except:
            help_msg = "Help is not working"
        return self.send_text(help_msg, data["chat_id"])

    def __command_hello(self, data):
        return self.send_text("Hello, %s" % data["username"], data["chat_id"])

    def __command_latex(self, data):
        expr = data["text"].lstrip()
        expr = expr[len(self.__COMMANDS["latex"][0]):]

        subprocess.call(['latexit', expr])
        if not os.path.exists(self.__PIC_FILE):
            self.send_text("Failed to compile formula", data["chat_id"])
            return False
        ret = self.send_pic(self.__PIC_FILE, data)
        if ret == False:
            self.send_text("Failed to send picture", data["chat_id"])
            return False
        os.remove(self.__PIC_FILE)
        return True
#        return self.send_text("Still developing...", data["chat_id"])

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
            self.log_event('Error getting updates')
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
                self.log_event('Unknown update: %s' % update)
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
            self.log_event('Message (id%s) from %s (id%s): "%s"' % \
                (parameters["update_id"], \
                 parameters["username"],  \
                 parameters["chat_id"],   \
                 parameters["text"]))
            self.run_command(parameters)

    def run(self):
        while True:
            try:
                ret = self.check_updates()
                time.sleep(self.__INTERVAL)
            except KeyboardInterrupt:
                self.log_event("Interrupted by keyboard")
                break
