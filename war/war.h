#pragma once

#include <array>
#include <queue>
#include <stdexcept>

enum Winner { kFirst, kSecond, kNone };

struct GameResult {
    Winner winner;
    int turn;
};

inline std::tuple<std::queue<int>, std::queue<int>> ReadArray(const std::array<int, 5> &first_deck,
                                                              const std::array<int, 5> &second_deck) {
    std::queue<int> deck_que_first;
    for (auto& item : first_deck) {
        deck_que_first.push(item);
    }
    std::queue<int> deck_que_second;
    for (auto& item : second_deck) {
        deck_que_second.push(item);
    }
    return std::make_tuple(deck_que_first, deck_que_second);
}

inline void CheckGameOver(const std::queue<int>& first_queue,
                          const std::queue<int>& second_queue,
                          int counter,
                          bool& GameOver,
                          GameResult& result) {

    if (first_queue.empty() && !second_queue.empty()) {
        GameOver = true;
        result.winner = kSecond;
        result.turn = counter;
    } else if (second_queue.empty() && !first_queue.empty()) {
        GameOver = true;
        result.winner = kFirst;
        result.turn = counter;
    } else if (first_queue.empty() && second_queue.empty()) {
        GameOver = true;
        result.winner = kNone;
        result.turn = counter;
        return;
    }
    if (counter >= 1000000) {
        GameOver = true;
        result.winner = kNone;
        result.turn = counter;
    }

}

GameResult SimulateWarGame(const std::array<int, 5>& first_deck,
                           const std::array<int, 5>& second_deck) {

    auto [first_queue, second_queue] = ReadArray(first_deck, second_deck);

    size_t counter = 0;
    bool GameOver = false;
    GameResult result;

    while (!GameOver) {
        CheckGameOver(first_queue, second_queue, counter, GameOver, result);
        if (GameOver) {
            break;
        }

        int move_first = first_queue.front();
        first_queue.pop();
        int move_second = second_queue.front();
        second_queue.pop();

        ++counter;

        if ((move_first == 0 && move_second == 9)) {
            first_queue.push(move_first);
            first_queue.push(move_second);
        }
        else if ((move_second == 0 && move_first == 9)) {
            second_queue.push(move_first);
            second_queue.push(move_second);
        }
        else if (move_first > move_second) {
            first_queue.push(move_first);
            first_queue.push(move_second);
        }
        else if (move_second > move_first) {
            second_queue.push(move_first);
            second_queue.push(move_second);
        }
    }
    return result;
}
