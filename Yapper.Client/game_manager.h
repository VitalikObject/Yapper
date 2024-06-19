#pragma once

namespace Yapper::Client::Game {
    public enum GameStatus {
        Connecting,
        Logging,
        Logged,
        Failed
    };

    public ref class GameManager abstract sealed {
    public:
        static GameStatus gameStatus = GameStatus::Connecting;
        static bool isNameSet = false;
        static System::String^ Name = "Bulya";
    };
}