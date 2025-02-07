-- 1. TABLE DEFINATION

CREATE TABLE teamInfo (
    id INT(11) NOT NULL AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(50) DEFAULT NULL,
    country VARCHAR(50) DEFAULT NULL,
    estYear YEAR(4) DEFAULT NULL
);

CREATE TABLE matchInfo (
    id INT(11) NOT NULL AUTO_INCREMENT PRIMARY KEY,
    location VARCHAR(50) DEFAULT NULL,
    startTime TIME DEFAULT NULL,
    endTime TIME DEFAULT NULL,
    matchDate DATE DEFAULT NULL,
    teamId INT(11) DEFAULT NULL,
    oppositionTeamId INT(11) DEFAULT NULL,
    wonTeamId INT(11) DEFAULT NULL,
    umpireName VARCHAR(50) DEFAULT NULL,
    type VARCHAR(50) DEFAULT NULL,
    CONSTRAINT fk_team FOREIGN KEY (teamId) REFERENCES teaminfo(id) ON DELETE SET NULL ON UPDATE CASCADE,
    CONSTRAINT fk_opposition_team FOREIGN KEY (oppositionTeamId) REFERENCES teaminfo(id) ON DELETE SET NULL ON UPDATE CASCADE,
    CONSTRAINT fk_won_team FOREIGN KEY (wonTeamId) REFERENCES teaminfo(id) ON DELETE SET NULL ON UPDATE CASCADE
);

CREATE TABLE playerInfo (
    id INT(11) NOT NULL AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(50) DEFAULT NULL,
    birthdate DATE DEFAULT NULL,
    joinedYear YEAR(4) DEFAULT NULL,
    retirementYear YEAR(4) DEFAULT NULL
);

CREATE TABLE matchPlayedPlayerInfo (
    matchId INT(11),
    teamId INT(11) DEFAULT NULL,
    playerId INT(11) DEFAULT NULL,
    playingAs VARCHAR(50) DEFAULT NULL,
    CONSTRAINT fk_matchId FOREIGN KEY (matchId) REFERENCES matchInfo(id) ON DELETE SET NULL ON UPDATE CASCADE,
    CONSTRAINT fk_teamId FOREIGN KEY (teamId) REFERENCES teamInfo(id) ON DELETE SET NULL ON UPDATE CASCADE,
    CONSTRAINT fk_playerId FOREIGN KEY (playerId) REFERENCES playerInfo(id) ON DELETE SET NULL ON UPDATE CASCADE
);

-- 2. Inserting values in each table
INSERT INTO teamInfo (name, country, estYear) 
VALUES 
('India', 'India', 1932),
('Australia', 'Australia', 1977),
('England', 'England', 1970),
('South Africa', 'South Africa', 1989),
('New Zealand', 'New Zealand', 1930);

INSERT INTO playerInfo (name, birthdate, joinedYear, retirementYear) 
VALUES
('Ravindra Jadeja', '1988-11-06', 2008, NULL),
('Steve Smith', '1989-06-02', 2010, NULL),
('Joe Root', '1990-12-30', 2013, NULL),
('AB de Villiers', '1984-02-17', 2004, 2022),
('Kane Williamson', '1990-08-08', 2010, NULL),
('David Warner', '1986-10-27', 2009, NULL),
('Ben Stokes', '1991-06-04', 2013, NULL),
('Mitchell Starc', '1990-01-30', 2010, NULL),
('Jofra Archer', '1995-04-01', 2016, NULL),
('Pat Cummins', '1993-05-08', 2011, NULL);

INSERT INTO matchInfo (location, startTime, endTime, matchDate, teamId, oppositionTeamId, wonTeamId, umpireName, type) 
VALUES
('Melbourne Cricket Ground', '10:00:00', '14:00:00', '2025-01-15', 1, 2, 1, 'Aleem Dar', 'Test Match'),
('Lord\'s Cricket Ground', '11:00:00', '15:00:00', '2025-01-16', 2, 3, 3, 'Marais Erasmus', 'ODI Match'),
('Eden Gardens', '09:30:00', '13:30:00', '2025-02-10', 3, 4, 4, 'Ruth Willis', 'T20 Match'),
('Wankhede Stadium', '15:00:00', '19:00:00', '2025-02-12', 5, 1, 5, 'Richard Kettleborough', 'Test Match'),
('Sydney Cricket Ground', '11:00:00', '15:00:00', '2025-03-01', 2, 5, 2, 'Nigel Llong', 'ODI Match');

INSERT INTO matchPlayedPlayerInfo (matchId, teamId, playerId, playingAs) 
VALUES
(1, 1, 1, 'All-Rounder'),
(1, 1, 4, 'Batsman'),
(1, 2, 2, 'Batsman'),
(1, 2, 3, 'Bowler'), 
(2, 2, 2, 'All-Rounder'),
(2, 3, 5, 'Batsman'),
(3, 3, 3, 'All-Rounder'),
(4, 1, 1, 'Batsman'),
(4, 5, 5, 'Batsman'),
(5, 2, 2, 'All-Rounder'),
(5, 5, 6, 'Bowler'); 


-- 3. Perform Operations

-- 1. List names of the umpire when Indian team won
SELECT umpireName from matchinfo
WHERE `wonTeamId` = (SELECT id from teaminfo WHERE name = 'India');

-- 2. List names of the players who have not played single match. 
select p.name
from playerinfo p
LEFT JOIN matchPlayedPlayerInfo mp ON p.id = mp.playerId
WHERE mp.`matchId` IS NULL;

-- 3. Find batsman scored maximum runs and batsman scored minimum runs and display their names
ALTER TABLE playerinfo
ADD COLUMN runs INT(11) DEFAULT NULL;

SET @run_value := 100;

UPDATE playerInfo
JOIN (SELECT id FROM playerInfo) AS p
SET runs = (@run_value := @run_value + 100)

SELECT name FROM playerinfo p
left join matchplayedplayerinfo mp ON p.`id` = mp.`playerId` AND mp.`playingAs` = "Batsman"
ORDER BY runs ASC
LIMIT 1;

SELECT name FROM playerinfo p
left join matchplayedplayerinfo mp ON p.`id` = mp.`playerId` AND mp.`playingAs` = "Batsman"
ORDER BY runs DESC
LIMIT 1;

-- 4. Find bowler who has taken maximum wickets and bowler taken minimum wickets and display their names
ALTER TABLE playerinfo
ADD COLUMN wickets INT(11) DEFAULT NULL;

SET @wicket_value := 100;

UPDATE playerInfo
JOIN (SELECT id FROM playerInfo) AS p
SET wickets = (@wicket_value := @wicket_value + 100)

SELECT name FROM playerinfo p
left join matchplayedplayerinfo mp ON p.`id` = mp.`playerId` AND mp.`playingAs` = "Bowler"
ORDER BY wickets ASC
LIMIT 1;

SELECT name FROM playerinfo p
left join matchplayedplayerinfo mp ON p.`id` = mp.`playerId` AND mp.`playingAs` = "Bowler"
ORDER BY runs DESC
LIMIT 1;

-- 5. List name of all players for given country and number of matches he has played
SELECT 
    pi.name AS PlayerName,
    COUNT(mp.matchId) AS MatchesPlayed
FROM 
    playerInfo pi
LEFT JOIN 
    matchPlayedPlayerInfo mp ON pi.id = mp.playerId
LEFT JOIN 
    teamInfo t ON mp.teamId = t.id
WHERE 
    t.country = 'India'
GROUP BY 
    pi.id, pi.name;

-- 6. List names of the countries who played matches on given location 
SELECT DISTINCT 
    mi.location AS Location, 
    ti.country AS Country
FROM 
    matchInfo mi
JOIN 
    teamInfo ti 
ON 
    mi.teamId = ti.id OR mi.oppositionTeamId = ti.id;

-- 7. List team name and location of the matches they played
SELECT 
    ti.name AS TeamName, 
    mi.location AS MatchLocation
FROM 
    matchInfo mi
JOIN 
    teamInfo ti 
ON 
    mi.teamId = ti.id
UNION
SELECT 
    ti.name AS TeamName, 
    mi.location AS MatchLocation
FROM 
    matchInfo mi
JOIN 
    teamInfo ti 
ON 
    mi.oppositionTeamId = ti.id;

-- 8. List names of teams who have never played any matches
SELECT 
    ti.name AS TeamName
FROM 
    teamInfo ti
LEFT JOIN 
    matchInfo mi 
ON 
    ti.id = mi.teamId OR ti.id = mi.oppositionTeamId
WHERE 
    mi.id IS NULL;

-- 9. List names of the countries and total matches they played
SELECT 
    ti.country AS Country, 
    COUNT(mi.id) AS TotalMatchesPlayed
FROM 
    teamInfo ti
LEFT JOIN 
    matchInfo mi 
ON 
    ti.id = mi.teamId OR ti.id = mi.oppositionTeamId
GROUP BY 
    ti.country;

-- 10. List name of team, and name of teams against which they played matches and count they won
SELECT 
    ti1.name AS TeamName, 
    ti2.name AS OpponentTeam, 
    COUNT(*) AS Wins
FROM 
    matchInfo mi
JOIN 
    teamInfo ti1 ON mi.teamId = ti1.id
JOIN 
    teamInfo ti2 ON mi.oppositionTeamId = ti2.id
WHERE 
    mi.wonTeamId = mi.teamId
GROUP BY 
    ti1.name, ti2.name;
