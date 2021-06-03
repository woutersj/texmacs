
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
  cout << "привет при-вет\n" << lan->get_hyphens (utf8_to_cork("привет")) << "\n";
  cout << "достопримечательности до-сто-при-ме-ча-тель-но-сти\n" << lan->get_hyphens (utf8_to_cork("достопримечательности")) << "\n";
  cout << "перспективе пер-спек-ти-ве\n" << lan->get_hyphens (utf8_to_cork("перспективе")) << "\n";
  cout << "прямые пря-мые\n" << lan->get_hyphens (utf8_to_cork("прямые")) << "\n";
  cout << "параллельного па-рал-лель-но-го\n" << lan->get_hyphens (utf8_to_cork("параллельного")) << "\n";
  cout << "наложены на-ло-же-ны\n" << lan->get_hyphens (utf8_to_cork("наложены")) << "\n";
  cout << "проведена про-ве-де-на\n" << lan->get_hyphens (utf8_to_cork("проведена")) << "\n";
  cout << "реконструкции ре-кон-струк-ции\n" << lan->get_hyphens (utf8_to_cork("реконструкции")) << "\n";
  cout << "известными из-вест-ны-ми\n" << lan->get_hyphens (utf8_to_cork("известными")) << "\n";
  cout << "согласно со-глас-но\n" << lan->get_hyphens (utf8_to_cork("согласно")) << "\n";
  cout << "семиугольных се-ми-уголь-ных\n" << lan->get_hyphens (utf8_to_cork("семиугольных")) << "\n";
  
  lan = text_language ("english");
  cout << "manifests man-i-fests\n" << lan->get_hyphens ("manifests") << "\n";
  cout << "instruments in-stru-ments\n" << lan->get_hyphens ("instruments") << "\n";
  cout << "he he\n" << lan->get_hyphens ("he") << "\n";
  cout << "analyses anal-y-ses\n" << lan->get_hyphens ("analyses") << "\n";
  cout << "samples sam-ples\n" << lan->get_hyphens ("samples") << "\n";
  cout << "submits sub-mits\n" << lan->get_hyphens ("submits") << "\n";
  cout << "federal fed-eral\n" << lan->get_hyphens ("federal") << "\n";
  cout << "office of-fice\n" << lan->get_hyphens ("office") << "\n";
}
