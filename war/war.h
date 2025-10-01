#pragma once

#include <array>
#include <queue>
#include <stdexcept>

constexpr int MAX_TURNS = 1'000'000;
constexpr int MIN_CARD = 0;
constexpr int MAX_CARD = 9;

enum class Winner { kFirst, kSecond, kNone };

struct GameResult {
    Winner winner;
    int turn = 0;
};

inline std::queue<int> CreateQueue(const std::array<int, 5>& first_deck) {
    std::queue<int> queue;
    for (auto& item : first_deck) {
        queue.push(item);
    }
    return queue;
}

inline std::optional<GameResult> CheckGameOver(const std::queue<int>& first_queue,
                          const std::queue<int>& second_queue,
                          const int counter) {

    if (first_queue.empty() && !second_queue.empty()) {
        return GameResult{Winner::kSecond, counter};
    }
    if (second_queue.empty() && !first_queue.empty()) {
        return GameResult{Winner::kFirst, counter};
    }
    if (first_queue.empty() && second_queue.empty()) {
        return GameResult{Winner::kNone, counter};
    }

    return std::nullopt;
}

inline void PushCards(std::queue<int>* queue, int move_first, int move_second) {
    queue->push(move_first);
    queue->push(move_second);
}

GameResult SimulateWarGame(const std::array<int, 5>& first_deck,
                           const std::array<int, 5>& second_deck) {

    std::queue<int> first_queue = CreateQueue(first_deck);
    std::queue<int> second_queue = CreateQueue(second_deck);

    int counter = 0;

    while (counter < MAX_TURNS) {

        int move_first = first_queue.front();
        first_queue.pop();

        int move_second = second_queue.front();
        second_queue.pop();

        ++counter;

        const bool first_wins = (move_first == MIN_CARD && move_second == MAX_CARD) ||
    (move_first > move_second && !(move_first == MAX_CARD && move_second == MIN_CARD));

        if (first_wins) {
            PushCards(&first_queue, move_first, move_second);
        } else {
            PushCards(&second_queue, move_first, move_second);
        }


        if (auto check =  CheckGameOver(first_queue, second_queue, counter); check.has_value()) {
            return GameResult{check->winner, check->turn};
        }
    }
    return {Winner::kNone, counter};
}