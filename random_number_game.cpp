#include <algorithm>
#include <iostream>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

class Strategy {
public:
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
  bool execute_strategy() { return m_strategy->validate_strategy(m_table); }
  void show_table();
  void show_strategy();
};

class Observer {
public:
  virtual void update(std::vector<int> table) = 0;
};

class Player : public Observer {
public:
  Player_screen *m_screen;
  int id = rand() % 999 - 100;
  Player(Strategy *strategy) { m_screen = new Player_screen(strategy); }
  void update(std::vector<int> table) { m_screen->set_table(table); }
};

class Game {
private:
  Game() {
    for (int i = 0; i < 100; ++i) {
      number_list.push_back(i);
    }
  };

public:
  std::vector<int> table;
  std::vector<int> number_list;
  std::vector<Player *> player_list;

  static Game &get_instance() {
    static Game instance;
    return instance;
  }

  void register_player(Player *player) { player_list.push_back(player); }
  // void remove_player() {}
  void notify_player() {
    for (auto &player : player_list) {
      player->update(table);
    }
  }
  void print_table() {
    for (auto &number : table) {
      std::cout << number << '\t';
    }
    std::cout << '\n';
  }

  bool validate_winner() {
    for (auto &player : player_list) {
      if (player->m_screen->execute_strategy()) {
        std::cout << "ha ganado el jugador con id -> " << player->id << '\n';
        return true;
      }
    }
    return false;
  }
  void generate_numbers() {
    std::random_shuffle(number_list.begin(), number_list.end());
    table.push_back(number_list[0]);
    notify_player();
  }
  void start_game() {
    if (player_list.size() == 5) {
      generate_numbers();
      print_table();
      while (!validate_winner()) {
        generate_numbers();
        print_table();
        if (table.size() == 5) {
          table = {};
        }
      }
    } else
      std::cout << "ERROR, NO ENOUGHT PLAYERS \n";
  }
};

int main() {
  auto simulation = Game::get_instance();
  auto player1 = new Player(new All_even);
  auto player2 = new Player(new All_even);
  auto player3 = new Player(new All_even);
  auto player4 = new Player(new All_even);
  auto player5 = new Player(new All_even);

  simulation.register_player(player1);
  simulation.register_player(player2);
  simulation.register_player(player3);
  simulation.register_player(player4);
  simulation.register_player(player5);

  simulation.start_game();
}
