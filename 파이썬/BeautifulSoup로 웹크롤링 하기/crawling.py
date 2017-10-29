# -*- coding:UTF-8 -*-
from bs4 import BeautifulSoup
import urllib.request

# 출력 파일 명
OUTPUT_FILE_NAME = 'output.txt'
 # 긁어올 URL
URL = 'http://news.naver.com/main/read.nhn?mode=LSD&mid=shm&sid1=105&oid=001&aid=0009387795'

 # 크롤링 함수
def get_text(URL) :
    source_code_from_URL = urllib.request.urlopen(URL)
    soup = BeautifulSoup(source_code_from_URL, 'html.parser')#, from_encoding = 'utf-8')
    text = ''
    for item in soup.find_all('div', id = 'articleBodyContents') :
        text = text + str(item.find_all(text = True))

    return text

# 메인 함수
def main() :
    open_output_file = open('output.txt', 'w')#OUTPUT_FILE_NAME, 'w')
    result_text = get_text(URL)
    open_output_file.write(result_text)
    open_output_file.close()

    #result_text = result_text.encode('utf-8')
    #result_text = result_text.decode('unicode_escape')

    print(result_text)
if __name__ == '__main__':
    main()
