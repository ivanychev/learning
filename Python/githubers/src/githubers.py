
from os import listdir
import requests
import json

def get_biggest_id(path):
    files = listdir(path)
    string_ids = (f.rstrip(".json") for f in files if f.endswith(".json"))
    ids = map(lambda x: int(x), string_ids)
    if len(files) == 0:
        return 0
    return max(ids)

def get_next_users(since_id, number, login, password):
    req = "https://api.github.com/users?since=" + str(since_id) + "&per_page=" + str(number)
    r = requests.get(req, auth=(login, password))
    return r.json()

def save_users(jsons, path):
    if len(jsons) == 0:
        return None
    for x in jsons:
        f = open(path + str(x["id"]) + ".json", "w+")
        f.write(json.dumps(x, sort_keys=True, indent=2))
        f.close()
        last_id = x["id"]
    return last_id
