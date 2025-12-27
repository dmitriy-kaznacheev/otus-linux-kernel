#!/usr/bin/env python3

import os, sys
import typing


char = typing.NewType('char', str)
EXIT_FAILURE: int = 1


class ModuleAPI:
  
  def __init__(self) -> None:
    try:
      self.f_str = open('/sys/module/hw_module/parameters/my_str', 'r')
      self.f_val = open('/sys/module/hw_module/parameters/ch_val', 'r+')
      self.f_idx = open('/sys/module/hw_module/parameters/idx', 'r+')
    except Exception as e:
      print('ERROR: cannot access to files from sys')
      os._exit(EXIT_FAILURE)
  
  def __dell__(self) -> None:
    self.f_str.close()
    self.f_val.close()
    self.f_idx.close()

  def set_character(self, pos: int, val: char) -> None:
    self.f_idx.write(str(pos))
    self.f_idx.flush()
    self.f_val.write(val)
    self.f_val.flush()

  def get_character(self, pos: int) -> char:
    self.f_idx.write(str(pos))
    self.f_idx.flush()
    self.f_val.seek(0)
    return self.f_val.read(1)

  def get_text(self) -> str:
    self.f_str.seek(0)
    return self.f_str.read()


class ModuleChecker:

  def __init__(self, text: str) -> None:
    self.api = ModuleAPI()
    self.text: str = text
    self.num_total: int = 0
    self.num_passed: int = 0

  def __del__(self) -> None:
    percent: float = self.num_passed / self.num_total
    print(f'successful tests: {percent:.0%} ({self.num_passed}/{self.num_total})\n')

  def run(self) -> bool:
    self.__write_characters()
    self.__read_characters()
    self.__read_all_text()
    return (self.num_passed == self.num_total)

  def __write_characters(self) -> None:
    for (pos, val) in enumerate(self.text):
      self.api.set_character(pos, val)
      self.num_total += 1

  def __read_characters(self) -> None:
    for (pos, val) in enumerate(self.text):
      read_val: char = self.api.get_character(pos)
      if read_val != val:
        print(f"[ FAILED ] write/read character: actual='{read_val}' expected='{val}'")
      else:
        print(f"[ PASSED ] write/read character: '{read_val}'")
        self.num_passed += 1
    
  def __read_all_text(self) -> None:
    self.num_total += 1
    read_text: str = self.api.get_text()
    if read_text != self.text:
      print(f"[ FAILED ] read all text: actual='{read_text}' expected='{self.text}'")
    else:
      print(f"[ PASSED ] read all text: '{read_text}'")
      self.num_passed += 1


if __name__ == '__main__':
  checker = ModuleChecker('Hello, World!')
  is_all_successful: bool = checker.run()
  if not is_all_successful:
    sys.exit(EXIT_FAILURE)

