# Word Ladder
Given two words, the goal is to find a chain of words from one to the other, where each pair of adjacent words differ by only one letter. 
For example, given "love" and "hate", one ladder would be "love" to "cove" to "cave" to "have" to "hate". The challenge is to find the
ladder of the shortest length. For example, it turns out that a ladder of shortest length from "love" to "hate" is "love" to "hove" to 
"have" to "hate". 

There are four allowable transformations from one word to the next:
  
  • One letter may be replaced (e.g., "have" to "hate", or "big" to
    "pig").

  • One letter may be inserted anywhere in the word (e.g., "cow" to
    "crow", or "hat" to "chat", or "hat" to "hate"). 

  • One letter may be deleted (e.g., "chat" to "cat", or "rant" to "ant",
    or "ante" to "ant").

  • A pair of adjacent letters may be swapped (e.g., "rat" to "art", or
    "loin" to "lion").
    
To test my code, I used a large word list file of about 60,000 words. (The file came from an
open-source wordlist project that is hosted at wordlist.sourceforge.net.)
