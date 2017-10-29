import sqlite3

def viewDBdata(db, table) :
    #SQLite DB 연결
    conn = sqlite3.connect(db)

    # Connection 으로부터 Cursor 생성
    cur = conn.cursor()

    # SQL 쿼리 실행
    query = "select * from {0}".format(table)
    cur.execute(query)

    # 데이타 Fetch
    rows = cur.fetchall() # 모든 데이터를 한번에 클라이언트로 가져옴
    for row in rows :
        print(row)

    # Connection 닫기
    cur.close()

def saveDBtable(db, data) :
    conn = sqlite3.connect(db)
    cur = conn.cursor()

    sql = "insert into customer(name,category,region) values (?, ?, ?)"
    cur.executemany(sql, data)
    #DB테이블 만들기
    #sql = "CREATE TABLE test2 ( id integer primary key autoincrement, name text not null, category integer, region text)"
    #cur.execute(sql)
    conn.commit() # 트랜젝션의 내용을 DB에 반영함
    conn.close()

if __name__ == '__main__':
    f = open('dbText.txt', 'r')

    #matrix = [[0 for col in range(10)] for row in range(10)]
    matrix =[[0]*3 for row in range(4)]

    tempFile = f.read().splitlines()
    print(tempFile)

    for i, tf in enumerate(tempFile):
        print(str(i) + ': ' + tf)
        for j, saveFile in enumerate(tf.split()):
            matrix[i][j] = saveFile
            print(str(j) + ': ' + saveFile)

    print(matrix)
    f.close()

    # DB에 테이블 입력
    saveDBtable('testDB.db', matrix)

    # DB에 저장되어 있는 테이블값 출력
    viewDBdata('testDB.db', 'customer')
