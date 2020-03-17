#include "query_funcs.h"
#include <iomanip>

void add_player(connection *C, int team_id, int jersey_num, string first_name, string last_name,
                int mpg, int ppg, int rpg, int apg, double spg, double bpg)
{

    //transaction
    work w(*C);

    //build sql instruction
    stringstream tmp;
    tmp << "INSERT INTO player (team_id, uniform_num, first_name, last_name, mpg, ppg, rpg, apg, spg, bpg) VALUES (";
    tmp << team_id << ", " << jersey_num << ", ";
    tmp << w.quote(first_name) << ", " << w.quote(last_name) << ", ";
    tmp << mpg << ", " << ppg << ", " << rpg << ", " << apg << ", " << spg << ", " << bpg << "); ";

    try
    {
        w.exec(tmp.str());
        w.commit();
    }
    catch (sql_error const &e)
    {
        cerr
            << "Database error: " << e.what() << endl
            << "Query was: " << e.query() << endl;
    }
    catch (exception const &e)
    {
        cerr << e.what() << endl;
    }
}

void add_team(connection *C, string name, int state_id, int color_id, int wins, int losses)
{
    //transaction
    work w(*C);

    //build sql instruction
    stringstream tmp;
    tmp << "INSERT INTO team (name, state_id, color_id, wins, losses) VALUES (";
    tmp << w.quote(name) << ", " << state_id << ", " << color_id << ", " << wins << ", " << losses << "); ";

    try
    {
        w.exec(tmp.str());
        w.commit();
    }
    catch (sql_error const &e)
    {
        cerr
            << "Database error: " << e.what() << endl
            << "Query was: " << e.query() << endl;
    }
    catch (exception const &e)
    {
        cerr << e.what() << endl;
    }
}

void add_state(connection *C, string name)
{
    //transaction
    work w(*C);

    //build sql instruction
    stringstream tmp;
    tmp << "INSERT INTO STATE (NAME) VALUES (" << w.quote(name) << "); ";

    try
    {
        w.exec(tmp.str());
        w.commit();
    }
    catch (sql_error const &e)
    {
        cerr
            << "Database error: " << e.what() << endl
            << "Query was: " << e.query() << endl;
    }
    catch (exception const &e)
    {
        cerr << e.what() << endl;
    }
}

void add_color(connection *C, string name)
{
    //transaction
    work w(*C);

    //build sql instruction
    stringstream tmp;
    tmp << "INSERT INTO color (name) VALUES (" << w.quote(name) << "); ";

    try
    {
        w.exec(tmp.str());
        w.commit();
    }
    catch (sql_error const &e)
    {
        cerr
            << "Database error: " << e.what() << endl
            << "Query was: " << e.query() << endl;
    }
    catch (exception const &e)
    {
        cerr << e.what() << endl;
    }
}

void query1(connection *C,
            int use_mpg, int min_mpg, int max_mpg,
            int use_ppg, int min_ppg, int max_ppg,
            int use_rpg, int min_rpg, int max_rpg,
            int use_apg, int min_apg, int max_apg,
            int use_spg, double min_spg, double max_spg,
            int use_bpg, double min_bpg, double max_bpg)
{
    //tmp str for sql command
    stringstream sql;
    sql << "SELECT * FROM PLAYER ";

    bool first_line = true;

    //mpg
    if (use_mpg == 1)
    {
        //WHERE or AND according to first_line or not
        if (first_line)
        {
            sql << " WHERE ";
        }
        else
        {
            sql << " AND ";
        }
        first_line = false;

        sql << "(mpg BETWEEN " << min_mpg << " AND " << max_mpg << ") ";
    }
    //ppg
    if (use_ppg == 1)
    {
        //WHERE or AND according to first_line or not
        if (first_line)
        {
            sql << " WHERE ";
        }
        else
        {
            sql << " AND ";
        }
        first_line = false;

        sql << "(ppg BETWEEN " << min_ppg << " AND " << max_ppg << ") ";
    }

    //rpg
    if (use_rpg == 1)
    {
        //WHERE or AND according to first_line or not
        if (first_line)
        {
            sql << " WHERE ";
        }
        else
        {
            sql << " AND ";
        }
        first_line = false;

        sql << "(rpg BETWEEN " << min_rpg << " AND " << max_rpg << ") ";
    }
    //apg
    if (use_apg == 1)
    {
        //WHERE or AND according to first_line or not
        if (first_line)
        {
            sql << " WHERE ";
        }
        else
        {
            sql << " AND ";
        }
        first_line = false;

        sql << "(apg BETWEEN " << min_apg << " AND " << max_apg << ") ";
    }

    //spg
    if (use_spg == 1)
    {
        //WHERE or AND according to first_line or not
        if (first_line)
        {
            sql << " WHERE ";
        }
        else
        {
            sql << " AND ";
        }
        first_line = false;

        sql << "(spg BETWEEN " << min_spg << " AND " << max_spg << ") ";
    }

    //bpg
    if (use_bpg == 1)
    {
        //WHERE or AND according to first_line or not
        if (first_line)
        {
            sql << " WHERE ";
        }
        else
        {
            sql << " AND ";
        }
        first_line = false;

        sql << "(bpg BETWEEN " << min_bpg << " AND " << max_bpg << ") ";
    }

    //nontransaction
    nontransaction N(*C);
    result R(N.exec(sql.str()));

    cout << "PLAYER_ID TEAM_ID UNIFORM_NUM FIRST_NAME LAST_NAME MPG PPG RPG APG SPG BPG" << endl;

    for (auto i : R)
    {
        cout << i[0].as<int>() << " " << i[1].as<int>() << " " << i[2].as<int>() << " "
             << i[3].as<string>() << " " << i[4].as<string>() << " " << i[5].as<int>() << " "
             << i[6].as<int>() << " " << i[7].as<int>() << " " << i[8].as<int>() << " "
             << fixed << setprecision(1) << i[9].as<double>() << " " << i[10].as<double>() << endl;
    }
}

void query2(connection *C, string team_color)
{
    nontransaction n(*C);

    stringstream tmp;
    tmp << "SELECT TEAM.name FROM TEAM, COLOR WHERE team.color_id = color.color_id AND color.name = ";
    tmp << n.quote(team_color) + ";";

    result r(n.exec(tmp.str()));

    //print result
    cout << "NAME" << endl;
    for (auto i : r)
    {
        cout << i[0].as<string>() << endl;
    }
}

void query3(connection *C, string team_name)
{
    nontransaction N(*C);
    stringstream sql;
    sql << "SELECT player.first_name, player.last_name FROM player, team "
        << "WHERE player.team_id=team.team_id AND team.name=" << N.quote(team_name)
        << " ORDER BY ppg DESC;";

    result R(N.exec(sql.str()));

    cout << "FIRST_NAME LAST_NAME" << endl;
    for (auto r : R)
    {
        cout << r[0].as<string>() << " " << r[1].as<string>() << endl;
    }
}

void query4(connection *C, string team_state, string team_color)
{
    nontransaction N(*C);

    //sql cmd
    stringstream sql;
    sql << "SELECT player.first_name, player.last_name, player.uniform_num "
        << "FROM player, team, color, state WHERE player.team_id=team.team_id AND team.color_id = color.color_id AND "
        << "team.state_id=state.state_id AND state.name=" << N.quote(team_state) + " AND color.name = " + N.quote(team_color) + ";";
    result R(N.exec(sql.str()));

    //output
    cout << "FIRST_NAME LAST_NAME UNIFORM_NUM" << endl;
    for (auto r : R)
    {
        cout << r[0].as<string>() << " " << r[1].as<string>() << " " << r[2].as<int>() << endl;
    }
}

void query5(connection *C, int num_wins)
{
    nontransaction N(*C);
    stringstream sql;
    sql << "SELECT player.first_name, player.last_name, team.name, team.wins "
        << "FROM player, team WHERE player.team_id = team.team_id AND team.wins "
        << "> " << num_wins << ";";
    result R(N.exec(sql.str()));

    //output
    cout << "FIRST_NAME LAST_NAME NAME WINS" << endl;
    for (auto r : R)
    {
        cout << r[0].as<string>() << " " << r[1].as<string>() << " " << r[2].as<string>() << " " << r[3].as<int>() << endl;
    }
}
