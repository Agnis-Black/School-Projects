"""
war card game client and server
"""
import asyncio
from collections import namedtuple
from enum import Enum
import logging
import random
import socket
import socketserver
import _thread
import sys

"""
Namedtuples work like classes, but are much more lightweight so they end
up being faster. It would be a good idea to keep objects in each of these
for each game which contain the game's state, for instance things like the
socket, the cards given, the cards still available, etc.
"""
Game = namedtuple("Game", ["p1", "p2", "score1", "score2", "cards"])

class Command(Enum):
    """
    The byte values sent as the first byte of any message in the war protocol.
    """
    WANTGAME = 0
    GAMESTART = 1
    PLAYCARD = 2
    PLAYRESULT = 3


class Result(Enum):
    """
    The byte values sent as the payload byte of a PLAYRESULT message.
    """
    WIN = 0
    DRAW = 1
    LOSE = 2

def readexactly(sock, numbytes):
    """
    Accumulate exactly `numbytes` from `sock` and return those. If EOF is found
    before numbytes have been received, be sure to account for that here or in
    the caller.
    """
    # b'' used as byte string literal for accumulating 
    data = b''
    while len(data) < numbytes:
        packet = sock.recv(numbytes - len(data))
        if not packet:
            raise EOFError("Connection closed while reading")
        data += packet
    return data

def kill_game(game):
    """
    TODO: If either client sends a bad message, immediately nuke the game.
    """
    pass

def compare_cards(card1, card2):
    """
    TODO: Given an integer card representation, return -1 for card1 < card2,
    0 for card1 = card2, and 1 for card1 > card2
    """
    if card1 == card2:
        return 0

    # Adding edge cases
    # Comparing Ace and king cards (highest and lowest values)

    if card2 == 0 and card1 == 12:
        return -1

    if card1 == 0 and card2 == 12:
        return 1
    
    if card1 < card2:
        return -1
    # If cards are not equal, or card1 < card2 then remainder must be card1 > card2 
    return 1

def deal_cards():
    """
    TODO: Randomize a deck of cards (list of ints 0..51), and return two
    26 card "hands."
    """
    # Create deck as a list of integers from 0 to 51
    deck = list(range(52))
    
    # Shuffle randomly
    random.shuffle(deck)
    
    # Divide deck into two hands of 26 cards each
    hand1 = deck[:26]
    hand2 = deck[26:]
    
    # Return the two hands
    return hand1, hand2

def serve_game(host, port):
    """
    TODO: Open a socket for listening for new connections on host:port, and
    perform the war protocol to serve a game of war between each client.
    This function should run forever, continually serving clients.
    """
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    # bind the socket to a public host and a port
    server_socket.bind((host, port))
    # listen for incoming connections
    server_socket.listen()
    print(f"Server listening on {host}:{port}")

    # accept client connections
    while True:

        client_socket, client_address = server_socket.accept()
        print(f"Client connected from {client_address[0]}:{client_address[1]}")

        # receive data from the client
        data = client_socket.recv(1024).decode().strip()

        # process the data
        if data == "start":
            client_socket.send("Starting game...".encode())
        elif data == "stop":
            client_socket.send("Stopping game...".encode())
        else:
            client_socket.send("Unknown command.".encode())

        # close the client socket
        client_socket.close()

    # close the server socket
    server_socket.close()


async def limit_client(host, port, loop, sem):
    """
    Limit the number of clients currently executing.
    You do not need to change this function.
    """
    async with sem:
        return await client(host, port, loop)

async def client(host, port, loop):
    """
    Run an individual client on a given event loop.
    You do not need to change this function.
    """
    try:
        reader, writer = await asyncio.open_connection(host, port, loop=loop)
        # send want game
        writer.write(b"\0\0")
        card_msg = await reader.readexactly(27)
        myscore = 0
        for card in card_msg[1:]:
            writer.write(bytes([Command.PLAYCARD.value, card]))
            result = await reader.readexactly(2)
            if result[1] == Result.WIN.value:
                myscore += 1
            elif result[1] == Result.LOSE.value:
                myscore -= 1
        if myscore > 0:
            result = "won"
        elif myscore < 0:
            result = "lost"
        else:
            result = "drew"
        logging.debug("Game complete, I %s", result)
        writer.close()
        return 1
    except ConnectionResetError:
        logging.error("ConnectionResetError")
        return 0
    except asyncio.streams.IncompleteReadError:
        logging.error("asyncio.streams.IncompleteReadError")
        return 0
    except OSError:
        logging.error("OSError")
        return 0

def main(args):
    """
    Launch a client/server.
    """
    host = args[1]
    port = int(args[2])
    if args[0] == "server":
        try:
            # Your server should serve clients until the user presses ctrl+c.
            serve_game(host, port)
        except KeyboardInterrupt:
            pass
        return
    else:
        loop = asyncio.get_event_loop()

    if args[0] == "client":
        loop.run_until_complete(client(host, port, loop))
    elif args[0] == "clients":
        sem = asyncio.Semaphore(1000)
        num_clients = int(args[3])
        clients = [limit_client(host, port, loop, sem) for x in range(num_clients)]
        
        async def run_all_clients():
            """
            Use `as_completed` to spawn all clients simultaneously
            and collect their results in arbitrary order.
            """
            completed_clients = 0
            for client_result in asyncio.as_completed(clients):
                completed_clients += await client_result
            return completed_clients
        
        res = loop.run_until_complete(asyncio.Task(run_all_clients(), loop=loop))
        logging.info("%d completed clients", res)

    loop.close()

if __name__ == "__main__":
    logging.basicConfig(level=logging.INFO)
    main(sys.argv[1:])

