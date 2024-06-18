#!/usr/bin/python3

from collections import defaultdict


def main():
    n, k = [int(i) for i in input().split()]
    

    board = []
    for _ in range(n):
        board.append([int(i) for i in input().split()])

    rows = []
    for row_index in range(n):
        row = defaultdict(int)
        for j in range(n):
            row[board[row_index][j]] += 1
        rows.append(row)

    for row_index in range(n):
        col = defaultdict(int)
        for j in range(n):
            col[board[j][row_index]] += 1
        rows.append(col)

    diag = defaultdict(int)
    for i in range(n):
        diag[board[i][i]] += 1
    rows.append(diag)

    diag = defaultdict(int)
    for i in range(n):
        diag[board[i][n-i-1]] += 1
    rows.append(diag)

    for i, ball in enumerate([int(i) for i in input().split()]):
        for potential in rows:
            if ball in potential:
                potential[ball] -= 1
                if potential[ball] == 0:
                    del potential[ball]
                    if not potential:
                        print(i + 1)
                        return

if __name__ == "__main__":
    main()

