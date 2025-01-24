struct DATA_TYPE {
    int first;
    int second;
};

struct ANSWER_TYPE {
    int first;
    int second;

    bool invalid_encoding;

    friend bool operator==(const ANSWER_TYPE &a, const ANSWER_TYPE &b) {
        return a.first == b.first && a.second == b.second;
    }
};

constexpr size_t PIPE_BUFFER_SIZE = 1048576;
constexpr int MESSAGE_LIMIT = 1048576;
