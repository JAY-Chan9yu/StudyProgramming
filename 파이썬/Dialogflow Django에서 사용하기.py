# -*- coding:UTF-8 -*-
from dialogflow_lite.dialogflow import Dialogflow
client_access_token = '토근 key'

dialogflow = Dialogflow(client_access_token=client_access_token)
response = dialogflow.text_request('someTest')#.decode('unicode_escape')
print("".join(response))
response = dialogflow.text_request('hi')
print("".join(response))
test = "썸타는 방법"
test.decode('utf-8')
response = dialogflow.text_request(test)
print("".join(response))
