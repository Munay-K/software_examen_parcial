#include <iostream>
#include <map>
#include <stdlib.h>
#include <vector>

class Strategy {
  virtual bool validate_strategy(std::vector<int> table) = 0;
};

class All_even : public Strategy {
  bool validate_strategy(std::vector<int> table) {
    bool result = true;
    for (auto &number : table) {
      if (number % 2 != 0)
        return false;
    }
    return result;
  }
};

class All_uneven : public Strategy {
  bool validate_strategy(std::vector<int> table) {
    bool result = true;
    for (auto &number : table) {
      if (number % 2 == 0)
        return false;
    }
    return result;
  }
};

class One_prime : public Strategy {
  bool validate_strategy(std::vector<int> table) {
    bool result = true;
    for (auto &number : table) {
      if (number <= 1)
        return false;
      for (int i = 2; i < number; ++i)
        if (number % i == 0)
          return false;
    }
    return result;
  }
};

class Three_multiple_ten : public Strategy {
  bool validate_strategy(std::vector<int> table) {
    bool result = false;
    short counter = 0;
    for (auto &number : table) {
      if (number % 10 == 0)
        return false;
      if (counter == 3)
        return true;
    }
    return result;
  }
};

class Two_multiple_twtfive : public Strategy {
  bool validate_strategy(std::vector<int> table) {
    bool result = false;
    short counter = 0;
    for (auto &number : table) {
      if (number % 25 == 0)
        counter++;
      if (counter == 2)
        return true;
    }
    return result;
  }
};

// context
class Player_screen {
private:
  Strategy *m_strategy;
  std::vector<int> m_table;

public:
  Player_screen(Strategy *strategy = nullptr) : m_strategy(strategy) {}
  Player_screen() {}
  void set_strategy(Strategy *strategy) {
    delete m_strategy;
    m_strategy = strategy;
  }
  void set_table(std::vector<int> table) { m_table = table; };
  void show_table();
  void show_strategy();
};

class Observer {
public:
  virtual void update(std::vector<int> table) = 0;
};

class Player : public Observer {
private:
  Player_screen *m_screen;
  Player(Strategy *strategy) { m_screen = new Player_screen(strategy); }

public:
  void update(std::vector<int> table) { m_screen->set_table(table); }
};

class Game {
private:
  std::vector<int> table;
  std::vector<int> generate_numbers() {
    srand(time(0));
    std::vector<int> result;
    for (int i = 0; i < 5; ++i) {
      result.push_back(rand() % 99 + 1);
    }
    return result;
  }
  Game() { table = generate_numbers(); };

public:
  static Game& get_instance() {
	static Game instance;
	return instance;
  }

  std::vector<Player *> player_list;
  void register_player(Player *player) { player_list.push_back(player); }
  //void remove_player() {}
  void notify_player() {
    for (auto &player : player_list) {
      player->update(table);
    }
  }


};

int main() {
  auto simulation = Game::get_instance();

}
