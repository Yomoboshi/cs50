-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Checking reports
SELECT id, street, description
FROM crime_scene_reports
WHERE year = 2023 AND month = 7 AND day >= 28;
-- = took place at 10:15am at the Humphrey Street bakery, 3 witnesses – each mentions the bakery.
-- report id = 295

-- Checking interviews from that day, looking for 'thief/theft' & 'bakery'
SELECT transcript
FROM interviews
WHERE year = 2023 AND month = 7 AND day >= 28;
-- = look for cars leaving parking lot ~10 min after 10:15
-- = look for ATM withdrawals on Leggett Street, 28th before 10:15
-- = look for 1st flight out of Fiftyville on 29th
-- = look for <~60s calls on that day, use caller, receiver
-- target person =
--          28th left bakery, made tx on Leggett, made a call
--          29th flew out

-- flight booker = call receiver
-- flight passenger = caller


-- Checking airport id of Fiftyville airport
SELECT id
FROM airports
WHERE city = 'Fiftyville';
-- = 8

-- Checking flights on 29th
SELECT *
FROM flights
JOIN airports ON airports.id = flights.origin_airport_id
WHERE airports.id = 8 AND year = 2023 AND month = 7 AND day = 29
ORDER BY hour ASC, minute ASC
LIMIT 10;
-- = 1st flight out of town has id 4, flies to NY, LaGuardia

SELECT * FROM airports WHERE id = 4;


-- Checking parking lot activity
-- note: increased the time interval in case witnesses are not acurate
SELECT license_plate
FROM bakery_security_logs
WHERE  activity = 'exit' AND year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND minute BETWEEN 10 AND 35;
-- = 9 license plates exiting lot in the interval


-- Checking ATM transactions on Leggett Street, 28th
-- note: transactions do not have time & withdrawal can be mistaken for deposit, therefore, checking all
SELECT *
FROM atm_transactions
WHERE atm_location LIKE 'Leggett%' AND year = 2023 AND month = 7 AND day = 28;
-- = 9 txs


-- Checking <= 60s calls that day
SELECT *
FROM phone_calls
WHERE year = 2023 AND month = 7 AND day = 28 AND duration <= 60;


-- WHERE year = 2023 AND month = 7 AND day >= 28 AND hour = 10;
-- SELECT COUNT(license_plate) FROM bakery_security_logs WHERE year = 2023 AND month = 7 AND day = 23;

-- Trying to put the data together to with an intersection
WITH leaving_lot AS (
    SELECT license_plate
    FROM bakery_security_logs
    WHERE activity = 'exit' AND year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND minute BETWEEN 10 AND 35
),

made_tx AS (
    SELECT atm_transactions.account_number, person_id
    FROM atm_transactions
    JOIN bank_accounts ON atm_transactions.account_number = bank_accounts.account_number
    WHERE atm_location LIKE 'Leggett%'
    AND atm_transactions.year = 2023
    AND atm_transactions.month = 7
    AND atm_transactions.day = 28
),

made_call AS (
    SELECT caller
    FROM phone_calls
    WHERE year = 2023 AND month = 7 AND day = 28 AND duration <= 60
),

-- With only 1st flight returning nothing, widened the query for 10 flights
fiftyville_flights AS (
    SELECT flights.id AS flight_id, flights.origin_airport_id, flights.destination_airport_id,
           flights.year, flights.month, flights.day, flights.hour, flights.minute
    FROM flights
    JOIN airports ON airports.id = flights.origin_airport_id
    WHERE airports.city = 'Fiftyville'
    AND flights.year = 2023
    AND flights.month = 7
    AND flights.day = 29
    ORDER BY flights.hour ASC, flights.minute ASC
    LIMIT 10
),

was_on_flight AS (
    SELECT passport_number
    FROM passengers
    WHERE flight_id IN (SELECT flight_id FROM fiftyville_flights)
)

-- Final SELECT to combine the results
SELECT DISTINCT people.*
FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN made_tx ON bank_accounts.account_number = made_tx.account_number
JOIN made_call ON people.phone_number = made_call.caller
JOIN was_on_flight ON people.passport_number = was_on_flight.passport_number
WHERE people.license_plate IN (SELECT license_plate FROM leaving_lot)
AND people.id IN (SELECT person_id FROM made_tx)
AND people.phone_number IN (SELECT caller FROM made_call)
AND people.passport_number IN (SELECT passport_number FROM was_on_flight)
LIMIT 10;
-- = 3 possible thiefs (Taylor, Diana, Bruce), now need to pair the thief with the accomplice

suspects AS (
    SELECT DISTINCT
)

SELECT people.*
FROM people
WHERE


SELECT *
FROM people
JOIN passengers ON passengers.passport_number = people.passport_number
JOIN phone_calls ON phone_calls.caller = people.name
WHERE people.license_plate = (SELECT) AND people.name = AND
LIMIT 10;



WITH specified_people AS (
    SELECT 'Taylor' AS name, '(286) 555-6063' AS phone_number
    UNION ALL
    SELECT 'Diana', '(770) 555-1861'
    UNION ALL
    SELECT 'Bruce', '(367) 555-5533'
)

SELECT *
FROM phone_calls
WHERE year = 2023
AND month = 7
AND day = 28
AND caller IN (
    '(286) 555-6063', -- Taylor's phone number
    '(770) 555-1861', -- Diana's phone number
    '(367) 555-5533'  -- Bruce's phone number
    )
    AND phone_calls.duration < 60;

------- YOU NO WORK???????
WITH calls_on_28th AS (
    SELECT receiver
    FROM phone_calls
    WHERE year = 2023
    AND month = 7
    AND day = 28
    AND caller IN (
        '(286) 555-6063', -- Taylor's phone number
        '(770) 555-1861', -- Diana's phone number
        '(367) 555-5533'  -- Bruce's phone number
    )
    AND phone_calls.duration < 60
),

flights_on_29th AS (
    SELECT passengers.passport_number
    FROM flights
    JOIN passengers ON flights.id = passengers.flight_id
    WHERE flights.year = 2023
    AND flights.month = 7
    AND flights.day = 29
)

SELECT DISTINCT helpers.*
FROM people AS helpers
JOIN calls_on_28th ON helpers.phone_number = calls_on_28th.receiver
JOIN flights_on_29th ON helpers.passport_number = flights_on_29th.passport_number
WHERE helpers.phone_number IN (SELECT receiver FROM calls_on_28th)
AND helpers.passport_number IN (SELECT passport_number FROM flights_on_29th);
