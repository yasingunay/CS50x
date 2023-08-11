-- Keep a log of any SQL queries you execute as you solve the mystery.

--Key Informations about crime:
--the theft took place on July 28, 2021 and that it took place on Humphrey Street.


-- Check all tables in database to think where to start
.tables
-- airports              crime_scene_reports   people
-- atm_transactions      flights               phone_calls
-- bakery_security_logs  interviews
-- bank_accounts         passengers


-- Start to imvestigate with crime_scene_reports
.schema crime_scene_reports
-- CREATE TABLE crime_scene_reports (
--     id INTEGER,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     street TEXT,
--     description TEXT,
--     PRIMARY KEY(id)
-- );


-- Learn details of the theft
SELECT description FROM crime_scene_reports
WHERE day = 28 AND month = 7  AND  street = 'Humphrey Street';
--Theft of the CS50 duck took place at 10:15 am at the Humphrey Street bakery.
--Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.

--Key Informations about crime:
--on July 28, 2021
--at 10:15
--on Humphrey Street.
--the bakery


.schema interviews
-- CREATE TABLE interviews (
--     id INTEGER,
--     name TEXT,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     transcript TEXT,
--     PRIMARY KEY(id)
-- );


-- Check the testimonies of three witnesses
SELECT name, transcript FROM interviews
WHERE month = 7 AND day = 28;
--Ruth: Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
--If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.

--Eugene: I don't know the thief's name, but it was someone I recognized.
--Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.


--Raymond: As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
--In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
--The thief then asked the person on the other end of the phone to purchase the flight ticket.



.schema atm_transactions
-- CREATE TABLE atm_transactions (
--     id INTEGER,
--     account_number INTEGER,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     atm_location TEXT,
--     transaction_type TEXT,
--     amount INTEGER,
--     PRIMARY KEY(id)
-- );



.schema bank_accounts
-- CREATE TABLE bank_accounts (
--     account_number INTEGER,
--     person_id INTEGER,
--     creation_year INTEGER,
--     FOREIGN KEY(person_id) REFERENCES people(id)
-- );



--Look for ATM atm_transactions on that day
SELECT month, day, bank_accounts.account_number, name, transaction_type, amount
FROM atm_transactions
JOIN bank_accounts ON atm_transactions.account_number = bank_accounts.account_number
JOIN people ON bank_accounts.person_id = people.id
WHERE month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw';
-- +-------+-----+----------------+---------+------------------+--------+
-- | month | day | account_number |  name   | transaction_type | amount |
-- +-------+-----+----------------+---------+------------------+--------+
-- | 7     | 28  | 49610011       | Bruce   | withdraw         | 50     |
-- | 7     | 28  | 26013199       | Diana   | withdraw         | 35     |
-- | 7     | 28  | 16153065       | Brooke  | withdraw         | 80     |
-- | 7     | 28  | 28296815       | Kenny   | withdraw         | 20     |
-- | 7     | 28  | 25506511       | Iman    | withdraw         | 20     |
-- | 7     | 28  | 28500762       | Luca    | withdraw         | 48     |
-- | 7     | 28  | 76054385       | Taylor  | withdraw         | 60     |
-- | 7     | 28  | 81061156       | Benista | withdraw         | 30     |
-- +-------+-----+----------------+---------+------------------+--------+


--Key Informations about crime:
--on July 28, 2021
--at 10:15
--on Humphrey Street.
--the bakery
--Thief: Bruce / Diana / Brooke / Kenny / Iman / Luca / Taylor / Benista





.schema flights

-- CREATE TABLE flights (
--     id INTEGER,
--     origin_airport_id INTEGER,
--     destination_airport_id INTEGER,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     hour INTEGER,
--     minute INTEGER,
--     PRIMARY KEY(id),
--     FOREIGN KEY(origin_airport_id) REFERENCES airports(id),
--     FOREIGN KEY(destination_airport_id) REFERENCES airports(id)

-- );


-- Check next days destination flights
SELECT flights.id, full_name, city, month, day, hour, minute
FROM flights
JOIN airports ON flights.destination_airport_id = airports.id
WHERE month = 7 AND day = 29 ORDER BY hour;

-- +----+-------------------------------------+---------------+-------+-----+------+--------+
-- | id |              full_name              |     city      | month | day | hour | minute |
-- +----+-------------------------------------+---------------+-------+-----+------+--------+
-- | 36 | LaGuardia Airport                   | New York City | 7     | 29  | 8    | 20     |
-- | 43 | O'Hare International Airport        | Chicago       | 7     | 29  | 9    | 30     |
-- | 23 | San Francisco International Airport | San Francisco | 7     | 29  | 12   | 15     |
-- | 53 | Tokyo International Airport         | Tokyo         | 7     | 29  | 15   | 20     |
-- | 18 | Logan International Airport         | Boston        | 7     | 29  | 16   | 0      |
-- +----+-------------------------------------+---------------+-------+-----+------+--------+



--Key Informations about crime:
--on July 28, 2021
--at 10:15
--on Humphrey Street.
--the bakery
-- Destination: New York City (flight_id == 36)(Tomorrow's earliest flight)




.schema passengers

-- CREATE TABLE passengers (
--     flight_id INTEGER,
--     passport_number INTEGER,
--     seat TEXT,
--     FOREIGN KEY(flight_id) REFERENCES flights(id)
-- );

SELECT passengers.passport_number,name, seat name
FROM passengers
JOIN people ON passengers.passport_number = people.passport_number
WHERE flight_id = 36;

-- +-----------------+--------+------+
-- | passport_number |  name  | name |
-- +-----------------+--------+------+
-- | 7214083635      | Doris  | 2A   |
-- | 1695452385      | Sofia  | 3B   |
-- | 5773159633      | Bruce  | 4A   |
-- | 1540955065      | Edward | 5C   |
-- | 8294398571      | Kelsey | 6C   |
-- | 1988161715      | Taylor | 6D   |
-- | 9878712108      | Kenny  | 7A   |
-- | 8496433585      | Luca   | 7B   |
-- +-----------------+--------+------+


--Key Informations about crime:
--on July 28, 2021
--at 10:15
--on Humphrey Street.
--the bakery
-- Destination: New York City (flight_id == 36)



-- Comparison query 1: Compare atm withdraw names and passangers name in flight_id = 36
SELECT name FROM atm_transactions
JOIN bank_accounts ON atm_transactions.account_number = bank_accounts.account_number
JOIN people ON bank_accounts.person_id = people.id
WHERE month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw' AND name IN
    (SELECT name FROM passengers
     JOIN people ON passengers.passport_number = people.passport_number
     WHERE flight_id = 36);


--The thief can be one of four
-- +--------+
-- |  name  |
-- +--------+
-- | Bruce  |
-- | Kenny  |
-- | Luca   |
-- | Taylor |




--Search about the bakery
.schema bakery_security_logs
-- CREATE TABLE crime_scene_reports (
--     id INTEGER,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     street TEXT,
--     description TEXT,
--     PRIMARY KEY(id)
-- );


-- Check all bakery_security_logs table
SELECT * FROM bakery_security_logs

-- Look which car entered and exited from 10.15 until 10.25 on 28 July
SELECT month, day, hour, minute, activity, bakery_security_logs.license_plate, name FROM bakery_security_logs
JOIN people ON bakery_security_logs.license_plate = people.license_plate
WHERE month = 7 AND day = 28 AND hour = 10 AND (minute >= 15 AND  minute <= 25);
-- +-------+-----+------+--------+----------+---------------+---------+
-- | month | day | hour | minute | activity | license_plate |  name   |
-- +-------+-----+------+--------+----------+---------------+---------+
-- | 7     | 28  | 10   | 16     | exit     | 5P2BI95       | Vanessa |
-- | 7     | 28  | 10   | 18     | exit     | 94KL13X       | Bruce   |
-- | 7     | 28  | 10   | 18     | exit     | 6P58WS2       | Barry   |
-- | 7     | 28  | 10   | 19     | exit     | 4328GD8       | Luca    |
-- | 7     | 28  | 10   | 20     | exit     | G412CB7       | Sofia   |
-- | 7     | 28  | 10   | 21     | exit     | L93JTIZ       | Iman    |
-- | 7     | 28  | 10   | 23     | exit     | 322W7JE       | Diana   |
-- | 7     | 28  | 10   | 23     | exit     | 0NTHK55       | Kelsey  |



-- Comparison query 2: Compare bakery_security_logs licese_plate names and comparison query 1
SELECT name  FROM atm_transactions
JOIN bank_accounts ON atm_transactions.account_number = bank_accounts.account_number
JOIN people ON bank_accounts.person_id = people.id
WHERE month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw' AND name IN
    (SELECT name  FROM passengers
    JOIN people ON passengers.passport_number = people.passport_number
    WHERE flight_id = 36)AND name IN
        (SELECT name FROM bakery_security_logs
        JOIN people ON bakery_security_logs.license_plate = people.license_plate
        WHERE month = 7 AND day = 28 AND hour = 10 AND (minute >= 15 AND  minute <= 25));


--The thief can be one of two
-- +-------+
-- | name  |
-- +-------+
-- | Bruce |
-- | Luca  |







.schema phone_calls
-- CREATE TABLE phone_calls (
--     id INTEGER,
--     caller TEXT,
--     receiver TEXT,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     duration INTEGER,
--     PRIMARY KEY(id)
-- );


-- Check phone calls on that day
SELECT month, day, caller, caller.name, receiver, receiver.name, duration FROM phone_calls
JOIN people caller ON phone_calls.caller = caller.phone_number
JOIN people receiver ON phone_calls.receiver = receiver.phone_number
WHERE month = 7 AND day = 28 AND duration <=60;

-- +-------+-----+----------------+---------+----------------+------------+----------+
-- | month | day |     caller     |  name   |    receiver    |    name    | duration |
-- +-------+-----+----------------+---------+----------------+------------+----------+
-- | 7     | 28  | (130) 555-0289 | Sofia   | (996) 555-8899 | Jack       | 51       |
-- | 7     | 28  | (499) 555-9472 | Kelsey  | (892) 555-8872 | Larry      | 36       |
-- | 7     | 28  | (367) 555-5533 | Bruce   | (375) 555-8161 | Robin      | 45       |
-- | 7     | 28  | (609) 555-5876 | Kathryn | (389) 555-5198 | Luca       | 60       |
-- | 7     | 28  | (499) 555-9472 | Kelsey  | (717) 555-1342 | Melissa    | 50       |
-- | 7     | 28  | (286) 555-6063 | Taylor  | (676) 555-6554 | James      | 43       |
-- | 7     | 28  | (770) 555-1861 | Diana   | (725) 555-3243 | Philip     | 49       |
-- | 7     | 28  | (031) 555-6622 | Carina  | (910) 555-3251 | Jacqueline | 38       |
-- | 7     | 28  | (826) 555-1652 | Kenny   | (066) 555-9701 | Doris      | 55       |
-- | 7     | 28  | (338) 555-6650 | Benista | (704) 555-2131 | Anna       | 54       |
-- +-------+-----+----------------+---------+----------------+------------+----------+




-- Comparison query 3: Compare phone_calls caller names and comparison query 2
SELECT name  FROM atm_transactions
JOIN bank_accounts ON atm_transactions.account_number = bank_accounts.account_number
JOIN people ON bank_accounts.person_id = people.id
WHERE month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw' AND name IN
    (SELECT name  FROM passengers
    JOIN people ON passengers.passport_number = people.passport_number
    WHERE flight_id = 36) AND name IN
        (SELECT name FROM bakery_security_logs
        JOIN people ON bakery_security_logs.license_plate = people.license_plate
        WHERE month = 7 AND day = 28 AND hour = 10 AND (minute >= 15 AND  minute <= 25)) AND name IN
            (SELECT name FROM phone_calls
            JOIN people  ON phone_calls.caller = people.phone_number
            WHERE month = 7 AND day = 28 AND duration <=60);

--The thief
-- +-------+
-- | name  |
-- +-------+
-- | Bruce |



--Bruce called Robin

-- The THIEF is: Bruce
-- The city the thief ESCAPED TO: New York City
-- The ACCOMPLICE is: Robin






