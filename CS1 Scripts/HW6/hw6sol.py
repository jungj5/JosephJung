import parse_url_new
import urllib
import check2




url = raw_input("Please enter a url: ")
print
n = int(raw_input("Please enter a number: "))
print


all_links = [url]
all_links += parse_url_new.get_links(url)
unvisited = parse_url_new.get_links(url)

while len(all_links) <= n and len(unvisited) > 0:
    a = parse_url_new.get_links(unvisited.pop(0))
    temp = []
    for l in a:
        if l not in all_links: 
            all_links.append(l)
            unvisited.append(l)       
count = 0
count2 = 0
for i in range(len(all_links)):
    if "nottingham" in all_links[i] or "Nottingham" in all_links[i]:
        count += 1
    if "london" in all_links[i] or "London" in all_links[i]:
        count2 += 1
    
        
    
dictionary = dict()
for link in all_links:
    a = link.split("/")
    date = a[4]
    if date in dictionary:
        dictionary[date] += 1
    else:
        dictionary[date] = 1
alist = dictionary.keys()
alist = sorted(alist)
blist = dictionary.values()
blist = max(blist)
def findblist(blist):
    for item in dictionary:
        if dictionary[item] == blist:
            print item
ignorelist = []
read = open("ignore.txt", 'r')
for line in read:
    ignore = line.strip()
    ignorelist.append(ignore)
                
            
            



print
print "Part 1: All links in the order they were found"
for i in range(len(all_links)):
    print all_links[i]
print
print "Part 2: Counting URLs containing substrings"
print "Number containing 'nottingham' is:",count 
print "Number contain 'london' is:",count2
print
print "Part 3, modification dates:"
print "Earliest date:",alist[0], "with", dictionary[alist[0]], "changes"
print "Latest date:",alist[-1], "with", dictionary[alist[-1]], "changes"
print "Most modifications is", blist, ",dates are:"
findblist(blist)
print
print "Part 4:" 

dictionary2 = dict()
if len(all_links) < 26:
    all_links = all_links
else:
    all_links = all_links[:25]

for links in all_links:
    wordslist = []
    f = urllib.urlopen(links)
    fstring = f.read()
    rstring = check2.strip_html(fstring)
    wlist = check2.find_words(rstring)
    
    for words in wlist:
        if len(words) >= 4 and not words.lower() in ignorelist:
            wordslist.append(words)
            for words2 in wordslist:
                if words2 in dictionary2:
                    dictionary2[words2] += 1
                else:
                    dictionary2[words2] = 1                

    print links, "has", len(wordslist), "eligible words"   


alist2 = dictionary2.values()
blist2 = dictionary2.keys()  
list2 = []
for links in all_links:
    for key in blist2:
        if dictionary2[key] == max(alist2):
            
    
  





