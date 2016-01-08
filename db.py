import mysql.connector as db

def connect_db():
    db_name = 'BakalarQuest'
    con = db.connect(user='root', password='881002')
    cur = con.cursor()

    # Kreiraj bazu
    cur.execute('CREATE DATABASE IF NOT EXISTS ' + db_name + ';')
    con.database = db_name

    # Kreiraj tablicu SOBA
    cur.execute('SET FOREIGN_KEY_CHECKS=0; ')
    cur.execute('DROP TABLE IF EXISTS SOBA;')
    query = ('CREATE TABLE SOBA ('
    'id INT NOT NULL AUTO_INCREMENT, '
    'opis VARCHAR(1000), '
    's INT NOT NULL, '
    'i INT NOT NULL, '
    'j INT NOT NULL, '
    'z INT NOT NULL, '
    'd INT NOT NULL, '
    'g INT NOT NULL, '
    'PRIMARY KEY (id) );'
    )
    cur.execute(query)

    # Kreiraj tablicu IGRAC
    #cur.execute('DROP TABLE IF EXISTS IGRAC;')
    query = ('CREATE TABLE IF NOT EXISTS IGRAC ('
    'id INT NOT NULL AUTO_INCREMENT, '
    'nickname VARCHAR(20) NOT NULL, '
    'username VARCHAR(20) NOT NULL, '
    'password VARCHAR(25) NOT NULL, '
    'pozicija INT NOT NULL, '
    'UNIQUE (nickname), '
    'UNIQUE (username), '
    'FOREIGN KEY (pozicija) REFERENCES SOBA (id) '
    'ON DELETE CASCADE ON UPDATE CASCADE, '
    'PRIMARY KEY (id) );'
    )
    cur.execute(query)

    # Citaj datoteku sobe.csv

    dat = open("sobe.csv", "r", encoding="utf8")

    sobe = []
    for i in dat:
        i = i.rstrip()
        i = i.split("!")
        if i != ['']:
            sobe.append(i)
            
    for i in range(len(sobe)):
        for j in range(len(sobe[i])):
            head, sep, tail = sobe[i][j].partition('=')
            sobe[i][j] = tail

    dat.close()

    # Popuni tablicu SOBA

    for i in sobe:
        cur.execute('INSERT INTO SOBA VALUES (' + i[0] + ", '"
        + i[1].replace("'", "''") + "', " + i[2] + ', ' + i[3] + ', ' + i[4] + ', '
        + i[5] + ', ' + i[6] + ', ' + i[7] + ');'
        )
    con.commit()

    # Zavrsi

    cur.close()
    con.close()
    print('DB init script finished')
    return sobe
