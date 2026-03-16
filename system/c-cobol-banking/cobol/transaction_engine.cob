       IDENTIFICATION DIVISION.
       PROGRAM-ID. TRANSACTION-ENGINE.

       ENVIRONMENT DIVISION.
       INPUT-OUTPUT SECTION.
       FILE-CONTROL.
           SELECT REQUEST-FILE ASSIGN TO "runtime/request.txt"
               ORGANIZATION IS LINE SEQUENTIAL.
           SELECT RESPONSE-FILE ASSIGN TO "runtime/response.txt"
               ORGANIZATION IS LINE SEQUENTIAL.

       DATA DIVISION.
       FILE SECTION.
       FD REQUEST-FILE.
       01 REQUEST-RECORD               PIC X(200).

       FD RESPONSE-FILE.
       01 RESPONSE-RECORD              PIC X(200).

       WORKING-STORAGE SECTION.
       01 WS-REQUEST-LINE              PIC X(200).
       01 WS-RESPONSE-LINE             PIC X(200).

       01 WS-OP                        PIC X(20).
       01 WS-ACCOUNT-ID                PIC X(10).
       01 WS-CURRENT-BALANCE-TXT       PIC X(30).
       01 WS-AMOUNT-TXT                PIC X(30).

       01 WS-CURRENT-BALANCE           PIC S9(9)V99 VALUE 0.
       01 WS-AMOUNT                    PIC S9(9)V99 VALUE 0.
       01 WS-NEW-BALANCE               PIC S9(9)V99 VALUE 0.

       01 WS-NEW-BALANCE-TXT           PIC -Z(9)9.99.
       01 WS-STATUS                    PIC X(20).
       01 WS-CODE                      PIC X(30).
       01 WS-MESSAGE                   PIC X(80).

       PROCEDURE DIVISION.
       MAIN.
           OPEN INPUT REQUEST-FILE.
           READ REQUEST-FILE INTO WS-REQUEST-LINE
               AT END
                   MOVE "REJECTED" TO WS-STATUS
                   MOVE "INVALID_INPUT" TO WS-CODE
                   MOVE "Request vazia" TO WS-MESSAGE
                   MOVE 0 TO WS-NEW-BALANCE
                   GO TO WRITE-RESPONSE
           END-READ.
           CLOSE REQUEST-FILE.

           UNSTRING WS-REQUEST-LINE DELIMITED BY "|"
               INTO WS-OP
                    WS-ACCOUNT-ID
                    WS-CURRENT-BALANCE-TXT
                    WS-AMOUNT-TXT
           END-UNSTRING.

           COMPUTE WS-CURRENT-BALANCE = FUNCTION NUMVAL(WS-CURRENT-BALANCE-TXT).
           COMPUTE WS-AMOUNT = FUNCTION NUMVAL(WS-AMOUNT-TXT).
           MOVE WS-CURRENT-BALANCE TO WS-NEW-BALANCE.

           IF WS-AMOUNT <= 0
               MOVE "REJECTED" TO WS-STATUS
               MOVE "INVALID_AMOUNT" TO WS-CODE
               MOVE "Valor precisa ser maior que zero" TO WS-MESSAGE
               GO TO WRITE-RESPONSE
           END-IF.

           EVALUATE FUNCTION UPPER-CASE(FUNCTION TRIM(WS-OP))
               WHEN "DEPOSIT"
                   COMPUTE WS-NEW-BALANCE = WS-CURRENT-BALANCE + WS-AMOUNT
                   MOVE "APPROVED" TO WS-STATUS
                   MOVE "OK" TO WS-CODE
                   MOVE "Deposito aprovado" TO WS-MESSAGE
               WHEN "WITHDRAW"
                   IF WS-AMOUNT > WS-CURRENT-BALANCE
                       MOVE "REJECTED" TO WS-STATUS
                       MOVE "INSUFFICIENT_FUNDS" TO WS-CODE
                       MOVE "Saldo insuficiente" TO WS-MESSAGE
                   ELSE
                       COMPUTE WS-NEW-BALANCE = WS-CURRENT-BALANCE - WS-AMOUNT
                       MOVE "APPROVED" TO WS-STATUS
                       MOVE "OK" TO WS-CODE
                       MOVE "Saque aprovado" TO WS-MESSAGE
                   END-IF
               WHEN OTHER
                   MOVE "REJECTED" TO WS-STATUS
                   MOVE "UNKNOWN_OPERATION" TO WS-CODE
                   MOVE "Operacao nao suportada" TO WS-MESSAGE
           END-EVALUATE.

       WRITE-RESPONSE.
           MOVE WS-NEW-BALANCE TO WS-NEW-BALANCE-TXT.
           STRING
               FUNCTION TRIM(WS-STATUS)
               "|"
               FUNCTION TRIM(WS-NEW-BALANCE-TXT)
               "|"
               FUNCTION TRIM(WS-CODE)
               "|"
               FUNCTION TRIM(WS-MESSAGE)
               DELIMITED BY SIZE
               INTO WS-RESPONSE-LINE
           END-STRING.

           OPEN OUTPUT RESPONSE-FILE.
           WRITE RESPONSE-RECORD FROM WS-RESPONSE-LINE.
           CLOSE RESPONSE-FILE.

           STOP RUN.
