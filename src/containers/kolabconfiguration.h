/*
 * Copyright (C) 2012  Christian Mollekopf <mollekopf@kolabsys.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef KOLABCONFIGURATION_H
#define KOLABCONFIGURATION_H
#include <string>
#include <vector>
#include <boost/scoped_ptr.hpp>
#include "kolabcontainers.h"

namespace Kolab {

struct Dictionary {
    Dictionary(){}
    Dictionary(const std::string &c): mLanguage(c){}

    bool operator==(const Dictionary &other) const {
        return mLanguage == other.mLanguage && mEntries == other.mEntries;
    }
    
    std::string language() const { return mLanguage; }

    void setEntries(const std::vector<std::string> &e){ mEntries = e; }
    std::vector<std::string> entries() const { return mEntries; }
private:
    std::string mLanguage;
    std::vector<std::string> mEntries;
};
    
struct CategoryColor {
    CategoryColor(){}
    CategoryColor(const std::string &c): mCategory(c) {}

    bool operator==(const CategoryColor &other) const {
        return mCategory == other.mCategory && mColor == other.mColor && mSubcategories == other.mSubcategories;
    }
    
    std::string category() const { return mCategory; }

    void setColor(const std::string &c) { mColor = c; }
    std::string color() const { return mColor; }

    void setSubcategories(const std::vector<CategoryColor> &c) { mSubcategories = c; }
    std::vector<CategoryColor> subcategories() const { return mSubcategories; }
private:
    std::string mCategory;
    std::string mColor;
    std::vector<CategoryColor> mSubcategories;
};

struct Snippet {
    enum TextType {
        Plain,
        HTML
    };

    Snippet(): mTextType(Plain) {}
    Snippet(const std::string &name, const std::string &text): mName(name), mText(text), mTextType(Plain) {}

    bool operator==(const Snippet &other) const {
        return mName == other.mName && mText == other.mText && mTextType == other.mTextType && mShortcut == other.mShortcut;
    }

    std::string name() const { return mName; }
    std::string text() const { return mText; }

    void setTextType(TextType type) { mTextType = type; }
    TextType textType() const { return mTextType; }

    void setShortCut(const std::string &shortcut) { mShortcut = shortcut; }
    std::string shortCut() const { return mShortcut; }

private:
    std::string mName;
    std::string mText;
    TextType mTextType;
    std::string mShortcut;
};

struct SnippetsCollection {
    SnippetsCollection() {}
    SnippetsCollection(const std::string &name): mName(name) {}

    bool operator==(const SnippetsCollection &other) const {
        return mName == other.mName && mSnippets == other.mSnippets;
    }

    std::string name() const { return mName; }

    void setSnippets(const std::vector<Snippet> &snippets) { mSnippets = snippets; }
    std::vector<Snippet> snippets() const { return mSnippets; }

private:
    std::string mName;
    std::vector<Snippet> mSnippets;
};

class Configuration {
public:
    Configuration();
    Configuration(const std::vector<CategoryColor> &);
    Configuration(const Dictionary &);
    Configuration(const SnippetsCollection &);
    Configuration(const Configuration &);
    ~Configuration();
    void operator=(const Configuration &);
    
    bool isValid() const;

    void setUid(const std::string &);
    std::string uid() const;

    void setCreated(const cDateTime &);
    cDateTime created() const;

    void setLastModified(const cDateTime &);
    cDateTime lastModified() const;

    enum ConfigurationType {
        Invalid,
        TypeDictionary,
        TypeCategoryColor,
        TypeSnippet
    };
    ConfigurationType type() const;
    std::vector<CategoryColor> categoryColor() const;
    Dictionary dictionary() const;
    SnippetsCollection snippets() const;
private:
    struct Private;
    boost::scoped_ptr<Private> d;
};

} //Namespace

#endif // KOLABCONFIGURATION_H
