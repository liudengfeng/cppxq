/**
 * Copyright (c) 2018-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <chrono>
#include <map>
#include <mutex>
#include <random>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include <fmt/format.h>
#include <fmt/chrono.h>
#include <fmt/color.h>

#include <ctime>

namespace helper
{

  using namespace std;

  inline string print_bool(bool b)
  {
    return b ? "True" : "False";
  }

  inline string now()
  {
    time_t t = time(nullptr);
    string time_str = fmt::format("{:%Y-%m-%d %H:%M:%S}", fmt::localtime(t));
    return time_str;
  }

  inline string time_signature()
  {
    time_t t = time(nullptr);
    char mbstr[100];
    strftime(mbstr, sizeof(mbstr), "%y%m%d-%H%M%S", localtime(&t));
    return string(mbstr);
  }

  inline uint64_t sec_since_epoch_from_now()
  {
    auto now = chrono::system_clock::now();
    return chrono::duration_cast<chrono::seconds>(
               now.time_since_epoch())
        .count();
  }

  inline void report_elapsed_time(double seconds)
  {
    // std::cout << "elapsed time : " << seconds << " seconds"
    //           << "\n";
    fmt::print("elapsed time : {:.4f} seconds\n", seconds);
  }

  inline uint64_t get_seed(int game_idx)
  {
    // [TODO] Definitely not the right way, but working.
    auto now = chrono::system_clock::now();
    auto now_ms = chrono::time_point_cast<chrono::milliseconds>(now);
    auto value = now_ms.time_since_epoch();
    long duration = value.count();
    return (time(nullptr) * 1000 + duration + game_idx * 2341479) % 100000000;
  }

  // Input a sorted list.
  inline string get_gap_list(const vector<int> &l)
  {
    if (l.empty())
      return "";
    int last = l[0];
    size_t last_i = 0;
    string output = to_string(last);

    for (size_t i = 1; i < l.size(); ++i)
    {
      if (l[i] > last + static_cast<int>(i - last_i))
      {
        if (l[i - 1] > last)
          output += "-" + to_string(l[i - 1]);
        last = l[i];
        last_i = i;
        output += ", " + to_string(last);
      }
      else if (i == l.size() - 1)
      {
        output += "-" + to_string(l[i]);
      }
    }
    return output;
  }

  inline string trim(string &str)
  {
    str.erase(0, str.find_first_not_of(' ')); // prefixing spaces
    str.erase(str.find_last_not_of(' ') + 1); // surfixing spaces
    return str;
  }

  inline vector<string> split(const string &s, char delim)
  {
    stringstream ss(s);
    string item;
    vector<string> elems;
    while (getline(ss, item, delim))
    {
      elems.push_back(move(item));
    }
    return elems;
  }

  template <typename Map>
  const typename Map::mapped_type &map_get(
      const Map &m,
      const typename Map::key_type &k,
      const typename Map::mapped_type &def)
  {
    auto it = m.find(k);
    if (it == m.end())
      return def;
    else
      return it->second;
  }

  template <typename Map>
  const typename Map::mapped_type &map_inc(
      Map &m,
      const typename Map::key_type &k,
      const typename Map::mapped_type &default_value)
  {
    auto it = m.find(k);
    if (it == m.end())
    {
      auto res = m.insert(make_pair(k, default_value));
      return res.first->second;
    }
    else
    {
      it->second++;
      return it->second;
    }
  }

  template <typename Map>
  pair<typename Map::const_iterator, bool> map_get(
      const Map &m,
      const typename Map::key_type &k)
  {
    auto it = m.find(k);
    if (it == m.end())
    {
      return make_pair(m.end(), false);
    }
    else
    {
      return make_pair(it, true);
    }
  }

  template <typename Map>
  pair<typename Map::iterator, bool> map_get(
      Map &m,
      const typename Map::key_type &k)
  {
    auto it = m.find(k);
    if (it == m.end())
    {
      return make_pair(m.end(), false);
    }
    else
    {
      return make_pair(it, true);
    }
  }

  template <typename A>
  size_t sample_multinomial(
      const vector<pair<A, float>> &v,
      mt19937 *gen)
  {
    vector<float> accu(v.size() + 1);

    float Z = 0.0;
    for (const auto &vv : v)
    {
      Z += vv.second;
    }

    uniform_real_distribution<> dis(0, Z);
    float rd = dis(*gen);

    accu[0] = 0;
    for (size_t i = 1; i < accu.size(); i++)
    {
      accu[i] = v[i - 1].second + accu[i - 1];
      if (rd < accu[i])
      {
        return i - 1;
      }
    }

    return v.size() - 1;
  }

  class MyClock
  {
  private:
    chrono::time_point<chrono::system_clock> _time_start;
    map<string, pair<chrono::duration<double>, int>> _durations;

  public:
    MyClock() {}
    void restart()
    {
      for (auto it = _durations.begin(); it != _durations.end(); ++it)
      {
        it->second.first = chrono::duration<double>::zero();
        it->second.second = 0;
      }
      _time_start = chrono::system_clock::now();
    }

    void setStartPoint()
    {
      _time_start = chrono::system_clock::now();
    }

    string summary() const
    {
      stringstream ss;
      double total_time = 0;
      for (auto it = _durations.begin(); it != _durations.end(); ++it)
      {
        if (it->second.second > 0)
        {
          double v = it->second.first.count() * 1000 / it->second.second;
          ss << it->first << ": " << v << "ms. \n";
          total_time += v;
        }
      }
      ss << "累计：" << total_time << "ms.";
      return ss.str();
    }

    inline bool record(const string &item)
    {
      auto it = _durations.find(item);
      if (it == _durations.end())
      {
        it = _durations
                 .insert(make_pair(
                     item, make_pair(chrono::duration<double>(0), 0)))
                 .first;
      }

      auto time_tmp = chrono::system_clock::now();
      it->second.first += time_tmp - _time_start;
      it->second.second++;
      _time_start = time_tmp;
      return true;
    }
  };

  inline void print_debug(const string &msg)
  {
    fmt::print(fg(fmt::color::dark_salmon), "{}\n", msg);
    std::cout << std::flush;
  }

  inline void print_info(const string &msg)
  {
    fmt::print(fg(fmt::color::forest_green), "{}\n", msg);
    std::cout << std::flush;
  }

  inline void print_warning(const string &msg)
  {
    fmt::print(fg(fmt::color::yellow_green), "{}\n", msg);
    std::cout << std::flush;
  }

  inline void print_tip(const string msg)
  {
    fmt::print(fg(fmt::color::crimson), "{}\n", msg);
    std::cout << std::flush;
  }
} // namespace helper
