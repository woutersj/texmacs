
/******************************************************************************
* MODULE     : hyphenate_test.cpp
* COPYRIGHT  : (C) 2021  Jeroen Wouters
*******************************************************************************
* This software falls under the GNU general public license version 3 or later.
* It comes WITHOUT ANY WARRANTY WHATSOEVER. For details, see the file LICENSE
* in the root directory or <http://www.gnu.org/licenses/gpl-3.0.html>.
******************************************************************************/

#include "gtest/gtest.h"

#include "edit_typeset.hpp"

TEST (text_language, get_hyphens) {
  // Test basic patterns
  // Test words
  // Test predefined hyphenations
  language lan;
  lan = text_language ("russian");
  cout << "привет\n" << lan->get_hyphens (utf8_to_cork("привет")) << "\n";
  cout << "поднятого\n" << lan->get_hyphens (utf8_to_cork("поднятого")) << "\n";
  cout << "перспективе\n" << lan->get_hyphens (utf8_to_cork("перспективе")) << "\n";
  cout << "прямые\n" << lan->get_hyphens (utf8_to_cork("прямые")) << "\n";
  cout << "параллельного\n" << lan->get_hyphens (utf8_to_cork("параллельного")) << "\n";
  cout << "наложены\n" << lan->get_hyphens (utf8_to_cork("наложены")) << "\n";
  cout << "проведена\n" << lan->get_hyphens (utf8_to_cork("проведена")) << "\n";
  cout << "реконструкции\n" << lan->get_hyphens (utf8_to_cork("реконструкции")) << "\n";
  cout << "известными\n" << lan->get_hyphens (utf8_to_cork("известными")) << "\n";
  cout << "согласно\n" << lan->get_hyphens (utf8_to_cork("согласно")) << "\n";
  cout << "семиугольных\n" << lan->get_hyphens (utf8_to_cork("семиугольных")) << "\n";
  
  lan = text_language ("english");
  cout << "manifests\n" << lan->get_hyphens ("manifests") << "\n";
  cout << "instruments\n" << lan->get_hyphens ("instruments") << "\n";
  cout << "he\n" << lan->get_hyphens ("he") << "\n";
  cout << "analyses\n" << lan->get_hyphens ("analyses") << "\n";
  cout << "samples\n" << lan->get_hyphens ("samples") << "\n";
  cout << "submits\n" << lan->get_hyphens ("submits") << "\n";
  cout << "federal\n" << lan->get_hyphens ("federal") << "\n";
  cout << "office\n" << lan->get_hyphens ("office") << "\n";
}
