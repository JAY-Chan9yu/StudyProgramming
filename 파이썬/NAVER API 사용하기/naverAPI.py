from bs4 import BeautifulSoup
import urllib.request
import re

def serchBlog(request) :
    client_id = "네이버 API 아이디"
    client_secret = "네이버 API 비밀번호"

    encText = urllib.request.quote(request)
    url = "https://openapi.naver.com/v1/search/blog.xml?query=" + encText

    request = urllib.request.Request(url)
    request.add_header("X-Naver-Client-Id",client_id)
    request.add_header("X-Naver-Client-Secret",client_secret)

    response = urllib.request.urlopen(request)
    rescode = response.getcode()

    if(rescode == 200) :
        response_body = response.read()
        soup = BeautifulSoup(response_body, 'html.parser')
        linkList = []
        # title 저장
        for question in soup.find_all('title') :
            linkList.append(question.string)
        # 블로그 link 저장
        for i, question in enumerate(soup.find_all('bloggerlink')) :
            linkList[i] += "-" + str(question.string)
            # 검색 tile 및 필요없는 문자 삭제
            linkList[i] = re.sub('[<> /b]','', linkList[i])
            linkList[i] = re.sub(deleteTitle,'', linkList[i])
    else :
        linkList.append("Error Code : " + resCode)

    return linkList

if __name__ == '__main__':
    outLink = []
    outLink = serchBlog('안산맛집')

    # 필요없는 내용 삭제
    outLink.pop(0)
    outLink.pop(9)

    for s in outLink :
        print(s)
