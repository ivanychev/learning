import json

def read_config(path):
    f = open(path, "r")
    dic = json.loads(f.read())
    f.close()
    return dic["path"]