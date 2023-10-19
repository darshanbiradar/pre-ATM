# pre-ATM
Title: Automated Teller Machine (ATM) System Implementation in C
## Introduction
The Automated Teller Machine (ATM) System implemented in C is a text-based simulation of an ATM that allows users to perform various banking operations, including withdrawal, fund transfers, balance inquiries, and deposits. This implementation provides a basic understanding of how real-world ATM systems work and offers a hands-on experience of designing and coding an interactive software application.
## Overview of the Code
The code consists of several components, including data structures, file handling, user input validation, and multiple functions to handle different banking operations. Here's a brief overview of the key components:
### 1. Data Structures
- Card Structure: Represents the information stored on a user's ATM card, including the card number, PIN, expiry date, associated account number, and card status (blocked or active).
- Account Structure: Stores details about a bank account, such as the account number, account holder's name, date of birth, account balance, and account status (active or inactive).
### 2. Functions
- ATM_init(): Initializes the ATM system with an initial balance of $100,000.
- fileread(char *s): Opens a file in read mode and returns a file pointer for further operations.
- card_autho(): Authenticates the user's card by verifying the card number and checking if the card is active or blocked.
- pin_autho(): Validates the user's PIN, allowing access to the account if the correct PIN is provided within three attempts. After three failed attempts, the card is blocked.
- acc_info_fetch(): Fetches account information from the database and matches it with the user's account number, ensuring it's a valid and active account.
- Withdraw(): Allows the user to withdraw funds from their account, with a maximum of three attempts. Validates the withdrawal amount and updates the account balance accordingly.
- transfer_funds(): Enables the user to transfer funds to another account. Validates the recipient's account number, checks for sufficient balance, and performs the transfer if conditions are met.
- deposit(): Allows the user to deposit funds into their account and updates the account balance accordingly.
- bal_enq(): Displays the current account balance to the user.
- select_operation(): Provides a menu-driven interface for users to choose different banking operations.
### 3. File Handling
- File Reading/Writing: Functions are provided to read from and write to text files containing card and account information.
- Error Handling: The code includes error handling for file operations, ensuring smooth execution even if the files are not accessible.
## User Interaction
Upon running the program, the user is welcomed and prompted to enter their card number and PIN. If the authentication is successful, the user can choose from various operations using the menu. Each operation is validated and executed accordingly, providing appropriate messages to the user.
## Conclusion
This C implementation of an ATM system serves as a valuable learning resource for beginners studying programming concepts, file handling, data structures, and user input validation. By understanding and dissecting this code, learners can grasp the complexities of real-world applications and gain insights into implementing secure and efficient banking systems.
Please note that this implementation is a simplified version and does not cover all aspects of a real ATM system, such as encryption, network communication, and database security. However, it lays a solid foundation for further exploration and development of more complex and secure banking applications.
