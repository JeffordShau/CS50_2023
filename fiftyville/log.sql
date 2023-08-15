-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT *
FROM crime_scene_reports
WHERE street = "Humphrey Street"
    AND month = 7
    AND day = 28
    AND year = 2021;
-- 10:15AM, Humphrey Street bakery, 3 witnesses, bakery

SELECT *
FROM interviews
WHERE month = 7
    AND day = 28
    AND year = 2021;
-- 1. Bakery parking lot, within 10 mins left, approx 10:25AM
-- 2. Eugene recognized, ATM Leggett Street, withdraw money
-- 3. Phone call, earliest flight tomorrow, accomplice purchase flight ticket

-- Bakery Logs
SELECT *
FROM bakery_security_logs
WHERE month = 7
    AND day = 28
    AND year = 2021
    AND hour = 10
    AND minute >= 15 AND minute <= 25;
-- License Plate: 5P2BI95, 94KL13X, 6P58WS2, 4328GD8, G412CB7, L93JTIZ, 322W7JE, 0NTHK55

-- atm
SELECT *
FROM atm_transactions
WHERE atm_location = "Leggett Street"
    AND month = 7
    AND day = 28
    AND year = 2021;

-- phone
SELECT *
FROM phone_calls
WHERE month = 7
    AND day = 28
    AND year = 2021;

-- airport
SELECT *
FROM flights
WHERE origin_airport_id =
    (SELECT id
    FROM airports
    WHERE city = "Fiftyville"
    )
    AND month = 7
    AND day = 29
    AND year = 2021;

_________________________________________________

SELECT name
FROM people
WHERE id IN
    (SELECT person_id
    FROM bank_accounts
    WHERE account_number IN
        -- bank acc
        (SELECT account_number
        FROM atm_transactions
        WHERE atm_location = "Leggett Street"
            AND month = 7
            AND day = 28
            AND year = 2021
            AND transaction_type = "withdraw"
        )
    )
    AND id IN
    (SELECT id
    FROM people
    WHERE license_plate IN
        (SELECT license_plate
        FROM bakery_security_logs
        WHERE month = 7
            AND day = 28
            AND year = 2021
            AND hour = 10
            AND minute >= 15 AND minute <= 25
            AND activity = "exit"
        )
    )
    AND id IN
    (SELECT id
    FROM people
    WHERE passport_number IN
        (SELECT passport_number
        FROM passengers
        WHERE flight_id IN
            -- flight info
            (SELECT id
            FROM flights
            WHERE origin_airport_id =
                (SELECT id
                FROM airports
                WHERE city = "Fiftyville"
                )
                AND month = 7
                AND day = 29
                AND year = 2021
            ORDER BY hour, minute
            LIMIT 1
            )
        )
    )
    AND id IN
    (SELECT id
    FROM people
    WHERE phone_number IN
        (SELECT caller
        FROM phone_calls
        WHERE month = 7
        AND day = 28
        AND year = 2021
        AND duration < 60
        )
    );
-- Bruce

SELECT name
FROM people
WHERE phone_number IN
    (SELECT receiver
    FROM phone_calls
    WHERE month = 7
        AND day = 28
        AND year = 2021
        AND duration < 60
        AND caller =
        (SELECT phone_number
        FROM people
        WHERE name = "Bruce"
        )
    )
-- Robin


SELECT city
FROM airports
WHERE id =
    (SELECT destination_airport_id
    FROM flights
    WHERE origin_airport_id =
        (SELECT id
        FROM airports
        WHERE city = "Fiftyville"
        )
        AND month = 7
        AND day = 29
        AND year = 2021
    ORDER BY hour, minute
    LIMIT 1
    )
-- New York City