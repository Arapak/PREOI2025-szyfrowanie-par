#include "parlib.h"

#include "communication.h"

namespace {

int a, b;

void readInput() { std::cin >> a >> b; }

}  // namespace

std::string printData(const DATA_TYPE &data) {
    std::stringstream s;
    s << ' ' << data.first << ' ' << data.second;
    return s.str();
}

template <>
void Child::run<CHILD_A>() {
    // uruchamiam encode
    auto encoded_pair = encode(std::pair<int, int>{a, b});
    DATA_TYPE encoded = {encoded_pair.first, encoded_pair.second};

    // sprawdzam czy zwrocilo poprawnie
    if (encoded.first == a || encoded.first == b || encoded.second == a || encoded.second == b ||
        encoded.first == encoded.second || encoded.first < 1 || encoded.first > 100 || encoded.second < 1 ||
        encoded.second > 100) {
        // tutaj kiedys bedziemy chcieli, zeby zwracalo errora
        exit(1);
    }

    userSend(encoded);
}

template <>
void Child::run<CHILD_B>() {
    auto encoded = userReceive<DATA_TYPE>();
    auto decoded = decode(std::make_pair(encoded.first, encoded.second));
    answer({decoded.first, decoded.second});
}

int main() {
    readInput();

    createPipes();
    forkAndRunChildren();

    try {
        auto [answer, _, message_length] = Master::masterMain();
        printExitMessage(ExitType::ANSWER, answer == ANSWER_TYPE{a, b});
    } catch (const CommunicationError &e) {
        panic(ErrorType::COMMUNICATION_ERROR);
    }
    return 0;
}
