-- Keep a log of any SQL queries you execute as you solve the mystery.

--- get basic information about crime
SELECT
    *
FROM
    crime_scene_reports
WHERE
    day = 28
    AND month = 7
    AND street = 'Humphrey Street';

-- get transcriptions and other information about interview
SELECT
    *
FROM
    interviews
WHERE
    day = 28
    AND month = 7
    AND transcript LIKE '%bakery%';

-- get information about exited visitors in the time
SELECT
    *
FROM
    bakery_security_logs
WHERE
    day = 28
    AND month = 7
    AND hour = 10
    AND minute >= 15
    AND minute <= 25;

-- get info about withdraw transactions at ATM at Leggett Street that day
SELECT
    *
FROM
    atm_transactions
WHERE
    day = 28
    AND month = 7
    AND atm_location = 'Leggett Street'
    AND transaction_type = 'withdraw';

-- get info about phone calls that day
SELECT
    *
FROM
    phone_calls
WHERE
    day = 28
    AND month = 7
    AND duration < 60;

-- get info about early flights from Fiftyville next day after crime
SELECT
    *
FROM
    flights
WHERE
    origin_airport_id = (
    SELECT
        id
    FROM
        airports
    WHERE
        city = 'Fiftyville')
    AND day = 29
ORDER BY
    hour,
    minute
LIMIT 1;

-- get passengers info at previous flight
SELECT
    *
FROM
    passengers
WHERE
    flight_id = (
    SELECT
        id
    FROM
        flights
    WHERE
        origin_airport_id = (
        SELECT
            id
        FROM
            airports
        WHERE
            city = 'Fiftyville')
        AND day = 29
    ORDER BY
        hour,
        minute
    LIMIT 1);

-- get info about escape city
SELECT
    city
FROM
    airports
WHERE
    id = (
    SELECT
        destination_airport_id
    FROM
        flights
    WHERE
        origin_airport_id = (
        SELECT
            id
        FROM
            airports
        WHERE
            city = 'Fiftyville')
        AND day = 29
    ORDER BY
        hour,
        minute
    LIMIT 1);

-- get name of the thief with previous info
SELECT
    passes.name as thief
FROM
    (
    SELECT
        name
    FROM
        people
    JOIN (
        SELECT
            *
        FROM
            bakery_security_logs
        WHERE
            day = 28
            AND month = 7
            AND hour = 10
            AND minute >= 15
            AND minute <= 25) as parking
ON
        parking.license_plate = people.license_plate) as park
JOIN
(
    SELECT
        name
    FROM
        people
    JOIN (
        SELECT
            *
        FROM
            passengers
        WHERE
            flight_id = (
            SELECT
                id
            FROM
                flights
            WHERE
                origin_airport_id = (
                SELECT
                    id
                FROM
                    airports
                WHERE
                    city = 'Fiftyville')
                AND day = 29
            ORDER BY
                hour,
                minute
            LIMIT 1)) as pass
ON
        pass.passport_number = people.passport_number) as passes ON
    park.name = passes.name
JOIN
(
    SELECT
        name
    FROM
        people
    WHERE
        id IN (
        SELECT
            person_id
        FROM
            bank_accounts
        WHERE
            account_number IN (
            SELECT
                account_number
            FROM
                atm_transactions
            WHERE
                day = 28
                AND month = 7
                AND atm_location = 'Leggett Street'
                AND transaction_type = 'withdraw'))) as accs
ON
    accs.name = passes.name
JOIN (
    SELECT
        name
    FROM
        people
    WHERE
        phone_number IN (
        SELECT
            caller
        FROM
            phone_calls
        WHERE
            day = 28
            AND month = 7
            AND duration < 60)
) as callers ON
    callers.name = accs.name;

-- get name of the accomplice with previous info
SELECT
    name as accomplice
FROM
    people
WHERE
    phone_number = (
    SELECT
        receiver
    FROM
        phone_calls
    WHERE
        caller = (
        SELECT
            phone_number
        FROM
            people
        WHERE
            name = (
            SELECT
                passes.name as thief
            FROM
                (
                SELECT
                    name
                FROM
                    people
                JOIN (
                    SELECT
                        *
                    FROM
                        bakery_security_logs
                    WHERE
                        day = 28
                        AND month = 7
                        AND hour = 10
                        AND minute >= 15
                        AND minute <= 25) as parking
ON
                    parking.license_plate = people.license_plate) as park
            JOIN
(
                SELECT
                    name
                FROM
                    people
                JOIN (
                    SELECT
                        *
                    FROM
                        passengers
                    WHERE
                        flight_id = (
                        SELECT
                            id
                        FROM
                            flights
                        WHERE
                            origin_airport_id = (
                            SELECT
                                id
                            FROM
                                airports
                            WHERE
                                city = 'Fiftyville')
                            AND day = 29
                        ORDER BY
                            hour,
                            minute
                        LIMIT 1)) as pass
ON
                    pass.passport_number = people.passport_number) as passes ON
                park.name = passes.name
            JOIN
(
                SELECT
                    name
                FROM
                    people
                WHERE
                    id IN (
                    SELECT
                        person_id
                    FROM
                        bank_accounts
                    WHERE
                        account_number IN (
                        SELECT
                            account_number
                        FROM
                            atm_transactions
                        WHERE
                            day = 28
                            AND month = 7
                            AND atm_location = 'Leggett Street'
                            AND transaction_type = 'withdraw'))) as accs
ON
                accs.name = passes.name
            JOIN (
                SELECT
                    name
                FROM
                    people
                WHERE
                    phone_number IN (
                    SELECT
                        caller
                    FROM
                        phone_calls
                    WHERE
                        day = 28
                        AND month = 7
                        AND duration < 60)
) as callers ON
                callers.name = accs.name))
        AND duration < 60);