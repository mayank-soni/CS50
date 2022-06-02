/* Log of SQL statements used to solve crime */

--CRIME SCENE REPORTS: Look for relevant crime scene reports from date and scene of crime
SELECT  description
FROM    crime_scene_reports
WHERE   year = 2021 AND month = 7 AND day = 28
AND     street = "Humphrey Street";

--WITNESS INTERVIEWS: Report mentions 3 witness interviews, all of which mention bakery. Find those interviews.
SELECT  *
FROM    interviews
WHERE   transcript LIKE "%bakery%";

--PARKING LOT: Ruth's interview mentions car leaving bakery within 10 minutes of crime. Get list of potential license plates.
SELECT  license_plate
FROM    bakery_security_logs
WHERE   year = 2021 AND month = 7 AND day = 28
AND     hour = 10 AND minute BETWEEN 15 AND 25
AND     activity = "exit";

--ATM RECORDS: Eugene's interview mentions seeing the criminal withdrawing money from an ATM on Leggett St earlier in the morning.
--Get list of potential account numbers.
SELECT  account_number
FROM    atm_transactions
WHERE   year = 2021 AND month = 7 AND day = 28
AND     atm_location = "Leggett Street"
AND     transaction_type = "withdraw";

--PHONE CALLS: Raymond's interview mentioned the person made a phone call while leaving bakery, for less than a minute.
--Get list of potential caller phone numbers
SELECT  caller
FROM    phone_calls
WHERE   year = 2021 AND month = 7 and day = 28
and     duration <= 60;

--FLIGHTS: Raymond's interview mentioned that on the phone call, the thief talked about taking the first flight out the next day
--and asked the person on the other side to buy the ticket.
--Get relevant passport numbers.
SELECT      passport_number
FROM        passengers
            JOIN    flights
            ON      passengers.flight_id = flights.id
WHERE       flights.id =
            (SELECT      flights.id
            FROM        flights
                        JOIN    airports
                        ON      airports.id = flights.origin_airport_id
            WHERE       airports.city = "Fiftyville"
            AND         year = 2021 AND month = 7 AND day = 29
            ORDER BY    hour, minute
            LIMIT       1);

--PEOPLE: See if anyone falls in all 3 lists: a. car, b. bank account, and c. passport number

SELECT  name
FROM    people
        JOIN    bank_accounts
        ON      people.id = bank_accounts.person_id
WHERE   account_number IN
        (SELECT account_number
        FROM    atm_transactions
        WHERE   year = 2021 AND month = 7 AND day = 28
        AND     atm_location = "Leggett Street"
        AND     transaction_type = "withdraw")
AND     phone_number IN
        (SELECT caller
        FROM    phone_calls
        WHERE   year = 2021 AND month = 7 and day = 28
        and     duration <= 60)
AND     passport_number IN
        (SELECT passport_number
        FROM    passengers
                JOIN    flights
                ON      passengers.flight_id = flights.id
        WHERE   flights.id =
                (SELECT     flights.id
                FROM        flights
                            JOIN    airports
                            ON      airports.id = flights.origin_airport_id
                WHERE       airports.city = "Fiftyville"
                AND         year = 2021 AND month = 7 AND day = 29
                ORDER BY    hour, minute
                LIMIT       1))
AND     license_plate IN
        (SELECT license_plate
        FROM    bakery_security_logs
        WHERE   year = 2021 AND month = 7 AND day = 28
        AND     hour = 10 AND minute BETWEEN 15 AND 25
        AND     activity = "exit");


-- Bruce is the criminal.
-- Get destination airport

SELECT      city
FROM        airports
WHERE       id =
            (SELECT  destination_airport_id
            FROM    flights
                    JOIN    airports
                    ON      airports.id = flights.origin_airport_id
            WHERE   airports.city =     "Fiftyville"
            AND     year = 2021 AND month = 7 AND day = 29
            ORDER BY    hour, minute
            LIMIT       1);

--Get name of accomplice
SELECT  name
FROM    people
WHERE   phone_number =
        (SELECT  receiver
        FROM    phone_calls
        WHERE   caller =
                (SELECT  phone_number
                FROM    people
                WHERE   id = 686048)
        AND     year = 2021 AND month = 7 and day = 28
        AND     duration <= 60);