# Corpus Search Tool

## Overview

This assignment involves creating a program that can process a given corpus in a specific format and answer user queries based on the information within the corpus. The goal is to develop a search mechanism that allows users to ask questions and retrieve relevant information from the corpus.

## Corpus Format

The corpus should be provided in a structured format, an example of which is given below. How to convert a pdf or txt file to the below mentioned format will be soon added.
```
('1', 0, 0, 1, 0) VOL.1: 1884 30 NOVEMBER, 1896 1
('1', 0, 1, 2, 32) 1. A CONFESSION 1
('1', 0, 2, 3, 50) [1884] I wrote it on a slip of paper and handed it to him myself.
('1', 0, 2, 4, 116) In this note not only did I confess my guilt, but I asked adequate punishment for it, and closed with a request to him not to punish himself for my offence.
```

## Complilation
- Make sure you have an OpenAI ChatGPT token with sufficient balance.
- To check or obtain your token and its balance, visit [OpenAI Billing Overview](https://platform.openai.com/account/billing/overview).
- You can request additional balance, typically $5, following the provided procedure.

```bash
git clone https://github.com/33Arsenic75/Corpus_Search_Tool.git
```
- Compile the files as
```bash
python3 -m venv./
pip install openai
openai migrate
g++ -std=c++11 tester.cpp qna_tool.cpp node.cpp dict.cpp search.cpp -w
```
- Terminal window will ask for your query followed by your GPT Token
- Output will be displayed in the terminal window.
