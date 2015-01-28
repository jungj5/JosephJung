# ----------------------------------------------------------------

def remove_inbetween( in_s, c0, c1):
    # Remove all of the html tags
    result_str = ''
    in_tag = False
    for c in in_s:
        if c == c0:
            in_tag = True
        elif c == c1:
            in_tag = False
        elif not in_tag:
            result_str += c
    return result_str

# ----------------------------------------------------------------

def strip_html(in_s):
    # Remove everything inbetween the tag delimiters
    result = remove_inbetween( in_s, '<', '>' )
    result = remove_inbetween( result, '{', '}' )
    return result

# ----------------------------------------------------------------

def find_words( rstring ):
    wlist = []
    i = 0
    while i < len(rstring):
        if rstring[i].isalpha():
            si = i
            i += 1
            while rstring[i].isalpha() or rstring[i] == "'":
                i += 1
            if si == 0 or rstring[si-1] != '&':
                wlist.append( rstring[si:i].lower() )
        else:
            i = i+1
    return wlist
