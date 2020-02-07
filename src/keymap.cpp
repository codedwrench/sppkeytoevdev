#include "keymap.h"

using namespace clsKeymapNamespace;

// Initialize keymap using initializer function
clsKeymap::clsKeymap() : mKeymap(InitKeymap())
{
}


const std::map<uint8_t, std::pair<int, bool>> clsKeymap::InitKeymap()
{
  std::vector<std::pair<uint8_t, std::pair<int,bool>>> lKeyVectorInitial =
  {{cEsc, {KEY_ESC, cPressed}},
   {cBackspace, {KEY_BACKSPACE, cPressed}},
   {cTab, {KEY_TAB, cPressed}},
   {cDelete, {KEY_DELETE, cPressed}},
   {cCapsLock, {KEY_CAPSLOCK, cPressed}},
   {cEnter, {KEY_ENTER, cPressed}},
   {cLeftShift, {KEY_LEFTSHIFT, cPressed}},
   {cRightShift, {KEY_RIGHTSHIFT,1}},
   {cLeftCtrl, {KEY_LEFTCTRL, cPressed}},
   {cFn, {KEY_FN, cPressed}},
   {cLeftWin, {KEY_LEFTMETA, cPressed}},
   {cLeftAlt, {KEY_LEFTALT, cPressed}},
   {cRightAlt, {KEY_RIGHTALT, cPressed}},
   {cSpacebar, {KEY_SPACE, cPressed}},
   {cUp, {KEY_UP, cPressed}},
   {cLeft, {KEY_LEFT, cPressed}},
   {cDown, {KEY_DOWN, cPressed}},
   {cRight, {KEY_RIGHT, cPressed}},
   {cOne, {KEY_1, cPressed}},
   {cTwo, {KEY_2, cPressed}},
   {cThree, {KEY_3, cPressed}},
   {cFour, {KEY_4, cPressed}},
   {cFive, {KEY_5, cPressed}},
   {cSix, {KEY_6, cPressed}},
   {cSeven, {KEY_7, cPressed}},
   {cEight, {KEY_8, cPressed}},
   {cNine, {KEY_9, cPressed}},
   {cZero, {KEY_0, cPressed}},
   {cA, {KEY_A, cPressed}},
   {cB, {KEY_B, cPressed}},
   {cC, {KEY_C, cPressed}},
   {cD, {KEY_D, cPressed}},
   {cE, {KEY_E, cPressed}},
   {cF, {KEY_F, cPressed}},
   {cG, {KEY_G, cPressed}},
   {cH, {KEY_H, cPressed}},
   {cI, {KEY_I, cPressed}},
   {cJ, {KEY_J, cPressed}},
   {cK, {KEY_K, cPressed}},
   {cL, {KEY_L, cPressed}},
   {cM, {KEY_M, cPressed}},
   {cN, {KEY_N, cPressed}},
   {cO, {KEY_O, cPressed}},
   {cP, {KEY_P, cPressed}},
   {cQ, {KEY_Q, cPressed}},
   {cR, {KEY_R, cPressed}},
   {cS, {KEY_S, cPressed}},
   {cT, {KEY_T, cPressed}},
   {cU, {KEY_U, cPressed}},
   {cV, {KEY_V, cPressed}},
   {cW, {KEY_W, cPressed}},
   {cX, {KEY_X, cPressed}},
   {cY, {KEY_Y, cPressed}},
   {cZ, {KEY_Z, cPressed}},
   {cGrave, {KEY_GRAVE, cPressed}},
   {cMinus, {KEY_MINUS, cPressed}},
   {cEqual, {KEY_EQUAL, cPressed}},
   {cLeftBrace, {KEY_LEFTBRACE, cPressed}},
   {cRightBrace, {KEY_RIGHTBRACE, cPressed}},
   {cBackSlash, {KEY_BACKSLASH, cPressed}},
   {cSemiColon, {KEY_SEMICOLON, cPressed}},
   {cApostrophe, {KEY_APOSTROPHE, cPressed}},
   {cComma, {KEY_COMMA, cPressed}},
   {cDot, {KEY_DOT, cPressed}}};


  // Add release keys
  // Copy the vector, since doing it in the same vector corrupts my data :(
  std::vector<std::pair<uint8_t, std::pair<int,bool>>> lKeyVectorFull(lKeyVectorInitial);

  for(auto const& [lKey, lValue] : lKeyVectorInitial)
  {
    lKeyVectorFull.push_back({lKey + cKeyReleaseOffset,
                             {lValue.first, cNotPressed}});
  }

  return std::map<uint8_t, std::pair<int, bool>>(lKeyVectorFull.begin(),
                                                 lKeyVectorFull.end());
}

const std::map<uint8_t, std::pair<int, bool>>&
clsKeymap::GetKeymap()
{
  return mKeymap;
}

const std::pair<int, bool>&
clsKeymap::ConvertKey(uint8_t aKey)
{
  return mKeymap.find(aKey)->second;
}
