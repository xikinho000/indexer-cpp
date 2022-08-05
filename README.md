Information Retrieval System - Indexer

This indexer is a very simple system, it creates a dictionary with a postings list containing the document occurences (Global) and the term frequency (Local). It contains a test collection in the accepted format to be processed.
The system function as any other traditional information retrieval system. It starts by removing stopwords, punctuations, stemming the words. Therefore, creating a list of unique terms that we will call it a Dictionary, each of the term in the dictionary will point to a list. The list contains each document that the term exist, counting each occurences in it.


