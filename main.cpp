#include <iostream>
#include <pqxx/pqxx>
#include <sstream>
#include <fstream>
#include <string>
#include "exerciser.h"

using namespace std;
using namespace pqxx;

//clean
void clean(string filename, connection *C)
{
  stringstream sql;
  string tmp;
  ifstream ifs;
  ifs.open(filename.c_str(), std::ifstream::in);
  while (getline(ifs, tmp))
  {
    sql << tmp;
  }
  ifs.close();

  //transaction
  work W(*C);
  W.exec(sql.str());
  W.commit();
}
void create_player(string filename, connection *C)
{
  string tmp;
  std::ifstream ifs;
  ifs.open(filename.c_str(), std::ifstream::in);
  while (std::getline(ifs, tmp))
  {
    stringstream ss;
    ss << tmp;

    int player_id, team_id, uniform_num, mpg, ppg, rpg, apg;
    string first_name, last_name;
    double spg, bpg;

    ss >> player_id >> team_id >> uniform_num >> first_name >> last_name >> mpg >> ppg >> rpg >> apg >> spg >> bpg;
    add_player(C, team_id, uniform_num, first_name, last_name, mpg, ppg, rpg, apg, spg, bpg);
  }
  ifs.close();
}

void create_team(string filename, connection *C)
{
  string tmp;
  std::ifstream ifs;
  ifs.open(filename.c_str(), std::ifstream::in);
  while (std::getline(ifs, tmp))
  {
    stringstream ss;
    ss << tmp;
    int team_id, state_id, color_id, wins, losses;
    string name;
    ss >> team_id >> name >> state_id >> color_id >> wins >> losses;
    add_team(C, name, state_id, color_id, wins, losses);
  }
  ifs.close();
}
void create_state(string filename, connection *C)
{
  string tmp;
  std::ifstream ifs;
  ifs.open(filename.c_str(), std::ifstream::in);
  while (std::getline(ifs, tmp))
  {
    stringstream ss;
    ss << tmp;

    string state_id, name;
    ss >> state_id >> name;
    add_state(C, name);
  }
  ifs.close();
}
void create_color(string filename, connection *C)
{
  string tmp;
  std::ifstream ifs;
  ifs.open(filename.c_str(), std::ifstream::in);
  while (std::getline(ifs, tmp))
  {
    stringstream ss;
    ss << tmp;

    string color_id, name;
    ss >> color_id >> name;
    add_color(C, name);
  }
  ifs.close();
}
int main(int argc, char *argv[])
{

  //Allocate & initialize a Postgres connection object
  connection *C;

  try
  {
    //Establish a connection to the database
    //Parameters: database name, user name, user password
    C = new connection("dbname=ACC_BBALL user=postgres password=passw0rd");
    if (C->is_open())
    {
      //first clean up db
      //TODO: create PLAYER, TEAM, STATE, and COLOR tables in the ACC_BBALL database
      //      load each table with rows from the provided source txt files

      clean("clean.sql", C);
      create_color("color.txt", C);

      create_state("state.txt", C);

      create_team("team.txt", C);

      create_player("player.txt", C);

      //test
      exercise(C);
    }
    else
    {
      cout << "Can't open database" << endl;
      return 1;
    }
  }
  catch (const std::exception &e)
  {
    cerr << e.what() << std::endl;
    return 1;
  }

  //Close database connection
  C->disconnect();
  return 0;
}
