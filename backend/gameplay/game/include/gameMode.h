#ifndef GAME_MODE_H
#define GAME_MODE_H

class GameMode {
    public:
        GameMode();
    
        bool getSpecialRule() const { return hasSpecialRule; }
        void setSpecialRule(bool rule) { hasSpecialRule = rule; }
    private:
        bool hasSpecialRule;
        std::string modeName;
        std::string description;
};

#endif // GAME_MODE_H