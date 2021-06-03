
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
#include "converter.hpp"

// should go into a shared file
void
my_goto_next_char (string s, int &i, bool utf8) {
  if (utf8) decode_from_utf8 (s, i);
  else if (i < N(s)) {
    if (s[i] == '<') {
      i++;
      while (i < N(s) && s[i] != '>') i++;
      if (i < N(s)) i++;
    }
    else i++;
  }
}

void
test_hyphens (language lan, string s, string t) {
  // cout << s << "  " << t << LF;
  array<int> penalty;
  penalty = lan->get_hyphens (s);
  string h = "";
  int i=0,j=0,k=0;
  for (i=0; i < N(s); my_goto_next_char(s,i,false),k++) {
    j = i;
    my_goto_next_char(s,j,false);
    h << s(i,j);
    if (penalty [k] == HYPH_STD) {
      h << "-";
    }
  }
  // cout << h << LF;
  EXPECT_EQ (h, t);
}

TEST (text_language, get_hyphens) {
  // Test basic patterns
  // Test words
  // Test predefined hyphenations
  language lan;
  lan = text_language ("russian");
  int repeats = 1000;
  for (int k=0;k<repeats;k++){
  test_hyphens (lan,utf8_to_cork("Нет"), utf8_to_cork("Нет"));
  test_hyphens (lan,utf8_to_cork("пять"), utf8_to_cork("пять"));
  test_hyphens (lan,utf8_to_cork("привет"), utf8_to_cork("при-вет"));
  test_hyphens (lan,utf8_to_cork("достопримечательности"), utf8_to_cork("до-сто-при-ме-ча-тель-но-сти"));
  test_hyphens (lan,utf8_to_cork("перспективе"), utf8_to_cork("пер-спек-ти-ве"));
  test_hyphens (lan,utf8_to_cork("прямые"), utf8_to_cork("пря-мые"));
  test_hyphens (lan,utf8_to_cork("параллельного"), utf8_to_cork("па-рал-лель-но-го"));
  test_hyphens (lan,utf8_to_cork("наложены"), utf8_to_cork("на-ло-же-ны"));
  
  test_hyphens (lan,utf8_to_cork("проведена"), utf8_to_cork("про-ве-де-на"));
  test_hyphens (lan,utf8_to_cork("реконструкции"), utf8_to_cork("ре-кон-струк-ции"));
  test_hyphens (lan,utf8_to_cork("известными"), utf8_to_cork("из-вест-ны-ми"));
  test_hyphens (lan,utf8_to_cork("согласно"), utf8_to_cork("со-глас-но"));
  test_hyphens (lan,utf8_to_cork("семиугольных"), utf8_to_cork("се-ми-уголь-ных"));
}
  
  lan = text_language ("english");
  for (int k=0;k<repeats;k++){
  test_hyphens (lan,string("baby"), string("baby"));
  test_hyphens (lan,string("manifests"), string("man-i-fests"));
  test_hyphens (lan,string("instruments"), string("in-stru-ments"));
  test_hyphens (lan,string("he"), string("he"));
  // texlive gives anal-y-ses, but hyphenate.py gives analy-ses
  // TeXmacs and hyphenate.py have an extra pattern "anal6ys" preventing the break after 'l'
  test_hyphens (lan,string("analyses"), string("analy-ses"));
  test_hyphens (lan,string("samples"), string("sam-ples"));
  test_hyphens (lan,string("submits"), string("sub-mits"));
  // texlive gives fed-eral, but hyphenate.py gives fed-er-al
  test_hyphens (lan,string("federal"), string("fed-er-al"));
  test_hyphens (lan,string("office"), string("of-fice"));
  test_hyphens (lan,string("supercalifragilisticexpialidocious"),
                string("su-per-cal-ifrag-ilis-tic-ex-pi-ali-do-cious"));
              }
}
