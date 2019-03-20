#include <iostream>
#include <omp.h>
#include <vector>
#include <queue>
#include <stdexcept>
#include <string>

double call(char s, double a, double b) {
  switch (s) {
    case '+': {
      return a + b;
    }
    case '-': {
      return a - b;
    }
    case '*': {
      return a * b;
    }
    case '/': {
      return a / b;
    }
    default: {
      throw std::logic_error("Not valid operation");
    }
  }
}

double parse(std::string& t, double prev_result) {
  double value2;
  double value1;
  char op = ' ';

  bool needOp =  false;
  bool firstTerm = true;

  int i = 0;
  while (i < t.size()) {
    if (std::isspace(t[i])) {
      ++i;
      continue;
    }
    if (needOp) {
      switch (t[i]) {
        case '+':
        case '-':
        case '*':
        case '/': {
          op = t[i];
          break;
        }
        default: {
          throw std::logic_error("Syntax error");
        }
      }
      needOp = false;
      ++i;
    } else {
      if (isdigit(t[i])) {
        value2 = 0;
        while (isdigit(t[i])) {
          value2 = value2 * 10 + std::stol(t.substr(i, 1));
          ++i;
        }
      } else if (t.size() - i >= 3 and
                t.substr(i, 3) == "res") {
        value2 = prev_result;
        i += 3;
      } else {
        throw std::logic_error("Syntax error");
      }

      if (firstTerm) {
        firstTerm = false;
        value1 = value2;
        needOp = true;
        continue;
      } else {
        break;
      }
    }
  }

  return call(op, value1, value2);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> t{"5 + 1",
                            "res / 2",
                            "24 / res",
                            "res * res",
                            "res - 6",
                            " res - 6  ",
                            "res - 6",
                            "res - 6",
                            "res - 6",};

  std::queue<std::string> tasks;
  std::queue<double> results;

#pragma omp parallel sections
  {
#pragma omp section
    {
      for (auto iter = t.begin(); iter != t.end(); ++iter) {
        auto& e = *iter;
        tasks.push(e);
        std::cout << "Client: Send task: " << e << std::endl;
        // wait run
        while (results.empty()) {}
        std::cout << "Client: Get result: " << results.front() << std::endl;
        results.pop();
      }
      tasks.push("");
    }
#pragma omp section
    {
      double prev_res = 0;
      while (true) {
        if (tasks.empty()) {
          continue;
        }
        auto task = tasks.front();
        tasks.pop();
        if (task.empty()) {
          break;
        }
        std::cout << "Server: Run task: " << task << std::endl;
        prev_res = parse(task, prev_res);
        std::cout << "Server: Send result: " << prev_res << std::endl;
        results.push(prev_res);
      }
    }
  }

}