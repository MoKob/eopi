#include <iostream>
#include <string>

#include "strings/algorithm.hpp"
#include "strings/random.hpp"

using namespace std;

int main() {
  cout << "aba"
       << " is " << eopi::strings::is_palindrom("aba") << " palindromic?"
       << endl;
  string replace_and_result("abba");
  cout << "Replace and remove: " << replace_and_result << " ";
  eopi::strings::remove_and_replace(4, replace_and_result);
  cout << replace_and_result << endl;

  cout << "Reverse sentences: \""
       << eopi::strings::reverse_words("This is a senctence")
       << "\" Word: " << eopi::strings::reverse_words("Word") << endl;

  cout << "Phone Mnemonics: 1234" << endl;

  eopi::strings::print_mnemonics(123);

  cout << "Look and say:\n" << endl;
  cout << eopi::strings::look_and_say(1) << endl;
  cout << eopi::strings::look_and_say(2) << endl;
  cout << eopi::strings::look_and_say(3) << endl;
  cout << eopi::strings::look_and_say(4) << endl;
  cout << eopi::strings::look_and_say(5) << endl;
  cout << eopi::strings::look_and_say(6) << endl;
  cout << eopi::strings::look_and_say(7) << endl;

  cout << "Romans\n";
  cout << "\tIV:" << eopi::strings::from_roman("IV") << endl;
  cout << "\tXXXIV:" << eopi::strings::from_roman("XXXIV") << endl;
  cout << "\tCLIX:" << eopi::strings::from_roman("CLIX") << endl;

  cout << "All Ips for 19216811\n";
  eopi::strings::all_valid_ips("19216811");

  cout << "Snakestring of \"Hello World!\n";
  cout << eopi::strings::snakestring("Hello World!") << endl;

  cout << "RLE of: "
       << "aaabbcCCCddddd" << endl;
  auto const encoding = eopi::strings::runlength::encode("aaabbcCCCddddd");
  cout << encoding << endl;
  cout << "Decoded: " << eopi::strings::runlength::decode(encoding) << endl;

  vector<uint32_t> egd = {13, 13};
  auto const encoded = eopi::strings::elias_gamma_code::encode(egd);
  cout << "Egc: " << encoded << endl;
  auto const decoded = eopi::strings::elias_gamma_code::decode(encoded);
  cout << "Decoded:";
  for (auto v : decoded)
    cout << " " << v;
  cout << endl;

  vector<string> justified = {"Hallo", "Welt", "was",  "ist",
                              "mit",   "dir",  "denn", "los"};
  eopi::strings::print_justified(justified, 11);

  string text =
      "Sed ut perspiciatis unde omnis iste natus error sit voluptatem "
      "accusantium doloremque laudantium, totam rem aperiam, eaque ipsa quae "
      "ab illo inventore veritatis et quasi architecto beatae vitae dicta "
      "sunt explicabo. Nemo enim ipsam voluptatem quia voluptas sit "
      "aspernatur aut odit aut fugit, sed quia consequuntur magni dolores "
      "eos qui ratione voluptatem sequi nesciunt. Neque porro quisquam est, "
      "qui dolorem ipsum quia dolor sit amet, consectetur, adipisci velit, "
      "sed quia non numquam eius modi tempora incidunt ut labore et dolore "
      "magnam aliquam quaerat voluptatem. Ut enim ad minima veniam, quis "
      "nostrum exercitationem ullam corporis suscipit laboriosam, nisi ut "
      "aliquid ex ea commodi consequatur? Quis autem vel eum iure "
      "reprehenderit qui in ea voluptate velit esse quam nihil molestiae "
      "consequatur, vel illum qui dolorem eum fugiat quo voluptas nulla "
      "pariatur? At vero eos et accusamus et iusto odio dignissimos ducimus "
      "qui blanditiis praesentium voluptatum deleniti atque corrupti quos "
      "dolores et quas molestias excepturi sint occaecati cupiditate non "
      "provident, similique sunt in culpa qui officia deserunt mollitia "
      "animi, id est laborum et dolorum fuga. Et harum quidem rerum facilis "
      "est et expedita distinctio. Nam libero tempore, cum soluta nobis est "
      "eligendi optio cumque nihil impedit quo minus id quod maxime placeat "
      "facere possimus, omnis voluptas assumenda est, omnis dolor "
      "repellendus. Temporibus autem quibusdam et aut officiis debitis aut "
      "rerum necessitatibus saepe eveniet ut et voluptates repudiandae sint "
      "et molestiae non recusandae. Itaque earum rerum hic tenetur a "
      "sapiente delectus, ut aut reiciendis voluptatibus maiores alias "
      "consequatur aut perferendis doloribus asperiores repellat.";

  string pattern = "sapiente";

  auto pos = eopi::strings::rabin_karp(text, pattern);
  cout << "Found pattern at: " << pos << std::endl;

  return 0;
}
