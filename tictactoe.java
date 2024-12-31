import java.util.InputMismatchException;
import java.util.Scanner;

public class tictactoe {
    private static char[][] board;
    private static final int SIZE = 3;
    private static char currentPlayer;

    public static void main(String[] args) {
        board = new char[SIZE][SIZE];
        currentPlayer = 'X';
        initializeBoard();

        while (true) {
            printBoard();
            try {
                playerMove();
                if (checkWinner()) {
                    printBoard();
                    System.out.println("Player " + currentPlayer + " wins!");
                    break;
                }
                if (isBoardFull()) {
                    printBoard();
                    System.out.println("The game is a tie!");
                    break;
                }
                switchPlayer();
            } catch (InputMismatchException e) {
                System.out.println("Invalid input. Please enter a number.");
                new Scanner(System.in).nextLine(); // Clear the invalid input
            } catch (Exception e) {
                System.out.println("An error occurred: " + e.getMessage());
            }
        }
    }

    private static void initializeBoard() {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                board[i][j] = '-';
            }
        }
    }

    private static void printBoard() {
        System.out.println("Current board:");
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                System.out.print(board[i][j] + " ");
            }
            System.out.println();
        }
    }

    private static void playerMove() throws InputMismatchException {
        Scanner scanner = new Scanner(System.in);
        int row, col;

        while (true) {
            try {
                System.out.println("Player " + currentPlayer + ", enter your move (row and column): ");
                row = scanner.nextInt() - 1;
                col = scanner.nextInt() - 1;

                if (row >= 0 && row < SIZE && col >= 0 && col < SIZE && board[row][col] == '-') {
                    board[row][col] = currentPlayer;
                    break;
                } else {
                    System.out.println("This move is not valid");
                }
            } catch (InputMismatchException e) {
                System.out.println("Invalid input. Please enter a number.");
                scanner.nextLine();  // Clear the invalid input
            }
        }
    }

    private static void switchPlayer() {
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    private static boolean checkWinner() {
        return (checkRows() || checkColumns() || checkDiagonals());
    }

    private static boolean checkRows() {
        for (int i = 0; i < SIZE; i++) {
            if (board[i][0] == currentPlayer && board[i][1] == currentPlayer && board[i][2] == currentPlayer) {
                return true;
            }
        }
        return false;
    }

    private static boolean checkColumns() {
        for (int i = 0; i < SIZE; i++) {
            if (board[0][i] == currentPlayer && board[1][i] == currentPlayer && board[2][i] == currentPlayer) {
                return true;
            }
        }
        return false;
    }

    private static boolean checkDiagonals() {
        if (board[0][0] == currentPlayer && board[1][1] == currentPlayer && board[2][2] == currentPlayer) {
            return true;
        }
        if (board[0][2] == currentPlayer && board[1][1] == currentPlayer && board[2][0] == currentPlayer) {
            return true;
        }
        return false;
    }

    private static boolean isBoardFull() {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == '-') {
                    return false;
                }
            }
        }
        return true;
    }
}

