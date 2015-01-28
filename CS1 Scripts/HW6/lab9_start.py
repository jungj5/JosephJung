import urllib


# Write this for Checkpoint 1
def remove_inbetween( in_s, c0, c1):
    result = ''
    a = False
    for char in in_s:
        if char == c0:
            a = True
        elif char == c1:
            a = False
        else:
            if a == False:
                result += char
    return result
                
            
                
        
        
            
            
            
            
            
                     
    


def strip_html(in_s):
    # Remove everything inbetween the tag delimiters
    result = remove_inbetween( in_s, '<', '>' )
    result = remove_inbetween( result, '{', '}' )
    return result


# Write this for Checkpoint 2
#isalpha
def find_words( rstring ):
    z = rstring.split()
    el = []
    b = False
    for a in z:
        if a.isalpha() == True or "'" in a == True:
            el.append(a)
        
    
            
    
    return el
    


'''
# Write this for Checkpoint 3
def count_words( wlist, common_set ):
'''
        


if __name__ == "__main__":
    url_name = raw_input("Enter the URL ==> " )

    # Open the URL and read in the entire html file into a single string
    f = urllib.urlopen(url_name)
    fstring = f.read()

    # Uncomment the following to test on a "known" html string
    """
    fstring = '''<html><head><title>HTML	example for CSCI-100</title> </head> <body> This 
        is a page about <a href="http://python.org">Python</a>. It contains links 
        and other       information.&ambs </body> </html> { Remove me } but include me {and not me}'''
    """

    # Output for Checkpoint 1
    rstring = strip_html(fstring)
    print rstring

    # Output for Checkpoint 2
    
    wlist = find_words(rstring)
    for w in wlist:
        print w


    # For Checkpoint 3, add code to read the file ignore.txt and store
    # it in a set called ignore_set, and then call count_words.  The
    # output should come from count_words.

    '''
    count_words( wlist, ignore_set )
    '''
