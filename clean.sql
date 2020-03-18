DROP TABLE IF EXISTS PLAYER CASCADE;
DROP TABLE IF EXISTS TEAM CASCADE;
DROP TABLE IF EXISTS COLOR CASCADE;
DROP TABLE IF EXISTS STATE CASCADE;

CREATE TABLE COLOR
(
    COLOR_ID SERIAL PRIMARY KEY,
    NAME varchar(1024)
);

CREATE TABLE STATE
(
    STATE_ID SERIAL PRIMARY KEY,
    NAME varchar(1024)
);

CREATE TABLE TEAM
(
    TEAM_ID SERIAL PRIMARY KEY,
    NAME varchar(1024),
    STATE_ID int,
    COLOR_ID int,
    WINS int,
    LOSSES int,
    CONSTRAINT STATE_FK FOREIGN KEY (STATE_ID) REFERENCES STATE(STATE_ID) ON DELETE SET NULL ON UPDATE CASCADE,
    CONSTRAINT COLOR_FK FOREIGN KEY (COLOR_ID) REFERENCES COLOR(COLOR_ID) ON DELETE SET NULL ON UPDATE CASCADE
);

CREATE TABLE PLAYER
(
    PLAYER_ID SERIAL PRIMARY KEY,
    TEAM_ID int,
    UNIFORM_NUM int,
    FIRST_NAME varchar(1024),
    LAST_NAME varchar(1024),
    MPG int,
    PPG int,
    RPG int,
    APG int,
    SPG float8,
    BPG float8,
    CONSTRAINT TEAM_FK FOREIGN KEY (TEAM_ID) REFERENCES TEAM(TEAM_ID) ON DELETE SET NULL ON UPDATE CASCADE
);
