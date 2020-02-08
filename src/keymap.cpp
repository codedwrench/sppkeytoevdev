#include "keymap.h"

using namespace clsKeymapNamespace;

// Initialize keymap using initializer function
clsKeymap::clsKeymap() : mKeymap(InitKeymap()), mFnKeymap(InitFnKeymap())
{
}


const std::map<uint8_t, std::pair<unsigned int, bool>>
clsKeymap::InitFnKeymap()
{
  std::vector<std::pair<uint8_t, std::pair<unsigned int,bool>>> lKeyVector =
  {{cZero, {KEY_VOLUMEUP, cPressed}},
   {cNine, {KEY_VOLUMEDOWN, cPressed}},
   {cEight, {KEY_MUTE, cPressed}},
   {cBackspace, {KEY_BLUETOOTH, cPressed}},
   {cSemiColon, {KEY_PAGEUP, cPressed}},
   {cApostrophe, {KEY_PAGEDOWN, cPressed}},
   {cLeft, {KEY_HOME, cPressed}},
   {cRight, {KEY_END, cPressed}},
   {cFn + cKeyReleaseOffset, {KEY_FN, cNotPressed}}};

  return std::map<uint8_t, std::pair<unsigned int, bool>>(lKeyVector.begin(),
                                                          lKeyVector.end());
}

const std::map<uint8_t, std::pair<unsigned int, bool>>
clsKeymap::InitKeymap()
{
  std::vector<
      std::pair<uint8_t, std::pair<unsigned int,bool>>> lKeyVectorInitial =
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
   {cDot, {KEY_DOT, cPressed}},
   {cSlash, {KEY_SLASH, cPressed}}};


  // Add release keys
  // Copy the vector, since doing it in the same vector corrupts my data :(
  std::vector<std::pair<uint8_t,
      std::pair<unsigned int,
      bool>>> lKeyVectorFull(lKeyVectorInitial);

  for(auto const& [lKey, lValue] : lKeyVectorInitial)
  {
    lKeyVectorFull.push_back({lKey + cKeyReleaseOffset,
                              {lValue.first, cNotPressed}});
  }

  return std::map<uint8_t,
      std::pair<unsigned int, bool>>(lKeyVectorFull.begin(),
                                     lKeyVectorFull.end());
}

const std::map<uint8_t, std::pair<unsigned int, bool>>&
clsKeymap::GetKeymap()
{
  return mKeymap;
}

const std::map<uint8_t, std::pair<unsigned int, bool>>&
clsKeymap::GetFnKeymap()
{
  return mFnKeymap;
}

/* If the fn key is pressed, all of the keys after it should be released right
 *  after press (easiest way to keep the key from being pressed after
 *  releasing fn before releasing the key) */
bool clsKeymap::GetImmediateRelease()
{
  return mFnKeyPressed;
}

void clsKeymap::SetFnKeyPressed(bool aFnKeyPressed)
{
  mFnKeyPressed = aFnKeyPressed;
}

const std::pair<unsigned int, bool> clsKeymap::ConvertKey(uint8_t aKey)
{    
  std::pair<unsigned int,bool> lKey = {0, false};

  if(!mFnKeyPressed)
  {
    const auto& lIterator = mKeymap.find(aKey);
    if(lIterator != mKeymap.end())
    {
      lKey = lIterator->second;
    }
  }
  else
  {
    const auto& lIterator = mFnKeymap.find(aKey);
    if(lIterator != mFnKeymap.end())
    {
      lKey = lIterator->second;
    }
  }

  if(lKey.first == KEY_FN)
  {
    mFnKeyPressed = lKey.second;
  }

  return lKey;
}



