📝 Word Autocorrection in Socket Chat (C Language)
This project is a simple yet powerful chat application built in C that enables real-time communication between a client and server using sockets. What makes it unique is the automatic word autocorrection feature, which detects and corrects misspelled words in messages using a large dictionary (up to 100,000 words).

🚀 Features
🔌 Client-Server Chat: Basic TCP socket communication between a client and server.

✏️ Word Autocorrection: Messages are checked for spelling and corrected before display.

📚 Large Dictionary Support: Can handle large wordlists efficiently.

⚙️ Custom Dictionary: Easily update or replace the wordlist for different languages or specialized vocabulary.

📁 Project Structure

├── client.c            # Client-side socket program
├── server.c            # Server-side socket program with autocorrection
├── autocorrect.h       # Header file for autocorrection functions(Levenshtein algorithm)
├── dictionary.txt      # Word list for spell checking
└── README.md           # This file
🛠️ How It Works
The server listens for incoming messages from the client.
When a message is received, the server checks each word against the dictionary.
If a word is misspelled, it is replaced with the closest match based on string similarity (Levenshtein distance).
The corrected message is then displayed or sent back to the client.

🧪 How to Use
Step 1: Compile the programs
Manually:

gcc server.c autocorrect.c -o server
gcc client.c -o client


Step 2: Run the server

./server

Step 3: Run the client in a separate terminal

./client
Step 4: Start chatting!
Messages typed in the client will be sent to the server.

The server will autocorrect the message and process it accordingly.

📄 Dictionary File
dictionary.txt should contain one valid word per line.

You can use any word list, such as /usr/share/dict/words or one from an open-source project.

The dictionary is loaded at runtime and stored in memory for fast access.

📚 Requirements
A C compiler

macOS (tested only on Mac)

No external libraries needed

🤝 Contributing
Contributions are welcome! If you find a bug or want to improve the autocorrection logic, feel free to fork this repo and open a pull request.

Fork the repository

Create a new branch: git checkout -b my-feature

Make your changes

Commit and push: git commit -m "Add feature" && git push

Open a pull request

📃 License
This project is open source under the MIT License. Feel free to use, modify, and distribute it.

Made with ❤️ in C for network programming learners and tinkerers.
