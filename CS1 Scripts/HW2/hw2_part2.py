def count_spaces(word):
    return word.count(' ')


#removing vowels


    
    
    
word = raw_input("Please enter a word: ")

spacedRemoved = word.replace(' ','')


vowelRemoved = spacedRemoved.replace('a','')
vowelRemoved  = vowelRemoved.replace('e','')
vowelRemoved  = vowelRemoved.replace('i','')
vowelRemoved  = vowelRemoved.replace('o','')
vowelRemoved  = vowelRemoved.replace('u','')

vowelRemoved = vowelRemoved.replace('A','')
vowelRemoved  = vowelRemoved.replace('E','')
vowelRemoved  = vowelRemoved.replace('I','')
vowelRemoved  = vowelRemoved.replace('O','')
vowelRemoved  = vowelRemoved.replace('U','')
lengthtotal = len(word.replace(' ',''))
number_vowel = lengthtotal - len(vowelRemoved)

number_consonant = len(vowelRemoved)

totalchar = number_vowel + number_consonant

lengthstrip = word.strip(' ')
print "Number of spaces at beginning and end of the string:", len(word) - len(lengthstrip)


#print "Number of spaces:", len(word) - totalchar




print "Number of vowels is:", lengthtotal - len(vowelRemoved)
print "Number of consonants is:", len(vowelRemoved)




print "Number of spaces:", count_spaces(word)
print "String with only consonants:", vowelRemoved
    