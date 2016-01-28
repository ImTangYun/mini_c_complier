
def generate(words, type):
    fd = open(words, 'rb');
    content = fd.read()
    all_word = content.split(' ')
    for word in all_word:
        if word != '' and not ('\n' in word):
            print '    key_word_dict_["' + word + '"] = ' + type + ';'; 

if __name__ == '__main__':

    generate('words1', 'OPRATION');
