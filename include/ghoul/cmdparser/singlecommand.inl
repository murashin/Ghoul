/*****************************************************************************************
 *                                                                                       *
 * GHOUL                                                                                 *
 * General Helpful Open Utility Library                                                  *
 *                                                                                       *
 * Copyright (c) 2012-2017                                                               *
 *                                                                                       *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this  *
 * software and associated documentation files (the "Software"), to deal in the Software *
 * without restriction, including without limitation the rights to use, copy, modify,    *
 * merge, publish, distribute, sublicense, and/or sell copies of the Software, and to    *
 * permit persons to whom the Software is furnished to do so, subject to the following   *
 * conditions:                                                                           *
 *                                                                                       *
 * The above copyright notice and this permission notice shall be included in all copies *
 * or substantial portions of the Software.                                              *
 *                                                                                       *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,   *
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A         *
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT    *
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF  *
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE  *
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                                         *
 ****************************************************************************************/

namespace ghoul::cmdparser  {

template<typename T, typename U, typename V, typename W>
SingleCommand<T, U, V, W>::SingleCommand(T* ptr1, std::string name, std::string shortName,
                                         std::string infoText, std::string parameterList)
    : CommandlineCommand(std::move(name), std::move(shortName), std::move(infoText),
                         std::move(parameterList), 1, MultipleCalls::No)
    , _ptr1(ptr1)
{
    ghoul_assert(_ptr1, "Ptr1 must not be nullptr");
}

template<typename T, typename U, typename V, typename W>
SingleCommand<T, U, V, W>::SingleCommand(T* ptr1, U* ptr2, std::string name,
                                         std::string shortName, std::string infoText,
                                         std::string parameterList)
    : CommandlineCommand(std::move(name), std::move(shortName), std::move(infoText),
                         std::move(parameterList), 2, MultipleCalls::No)
    , _ptr1(ptr1)
    , _ptr2(ptr2)
{
    ghoul_assert(_ptr1, "Ptr1 must not be nullptr");
    ghoul_assert(_ptr2, "Ptr2 must not be nullptr");
}

template<typename T, typename U, typename V, typename W>
SingleCommand<T, U, V, W>::SingleCommand(T* ptr1, U* ptr2, V* ptr3, std::string name,
                                         std::string shortName, std::string infoText,
                                         std::string parameterList)
    : CommandlineCommand(std::move(name), std::move(shortName), std::move(infoText),
                         std::move(parameterList), 3, MultipleCalls::No)
    , _ptr1(ptr1)
    , _ptr2(ptr2)
    , _ptr3(ptr3)
{
    ghoul_assert(_ptr1, "Ptr1 must not be nullptr");
    ghoul_assert(_ptr2, "Ptr2 must not be nullptr");
    ghoul_assert(_ptr3, "Ptr3 must not be nullptr");
}

template<typename T, typename U, typename V, typename W>
SingleCommand<T, U, V, W>::SingleCommand(T* ptr1, U* ptr2, V* ptr3, W* ptr4,
                                         std::string name, std::string shortName,
                                         std::string infoText, std::string parameterList)
    : CommandlineCommand(std::move(name), std::move(shortName), std::move(infoText),
                         std::move(parameterList), 4, MultipleCalls::No)
    , _ptr1(ptr1)
    , _ptr2(ptr2)
    , _ptr3(ptr3)
    , _ptr4(ptr4)
{
    ghoul_assert(_ptr1, "Ptr1 must not be nullptr");
    ghoul_assert(_ptr2, "Ptr2 must not be nullptr");
    ghoul_assert(_ptr3, "Ptr3 must not be nullptr");
    ghoul_assert(_ptr4, "Ptr4 must not be nullptr");
}

template<typename T, typename U, typename V, typename W>
void SingleCommand<T, U, V, W>::execute(const std::vector<std::string>& parameters) {
    *_ptr1 = cast<T>(parameters[0]);
    if (_ptr2) {
        *_ptr2 = cast<U>(parameters[1]);
    }
    if (_ptr3) {
        *_ptr3 = cast<V>(parameters[2]);
    }
    if (_ptr4) {
        *_ptr4 = cast<W>(parameters[3]);
    }
}

template<typename T, typename U, typename V, typename W>
void SingleCommand<T, U, V, W>::checkParameters(
                                        const std::vector<std::string>& parameters) const
{
    CommandlineCommand::checkParameters(parameters);
    is<T>(parameters[0]);

    if (_ptr2) {
        is<U>(parameters[1]);
    }

    if (_ptr3) {
        is<V>(parameters[2]);
    }

    if (_ptr4) {
        is<W>(parameters[3]);
    }
}

} // namespace ghoul::cmdparser
