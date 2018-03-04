import requests
import datetime
import time
import json

a = 'test'
if a == 'test' :
    print("etwets")
#url = 'http://127.0.0.1:8000/'
url = 'http://13.115.233.106/'
# String 포맷
obj={ "secret_key" : 'WlCksRb%6@2',"name" : 'TEST', "introduction" : "test", "gametime" : 10, "gamescore" : 22, "gamelevel" : 4 }
res = requests.post(url, data = obj)
print(res.text)
