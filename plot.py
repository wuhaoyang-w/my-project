import matplotlib.pyplot as plt
plt.switch_backend('Agg')
plt.rcParams["font.family"] = ["SimHei", "Microsoft YaHei", "DengXian"]
words=[]
counts=[]
with open("result.txt", "r", encoding="GBK") as f:
    textcontent=f.read()
lines=textcontent.splitlines()
flag=False
for line in lines:
    if "高频单词top5：" in line:
        flag=True
        continue
    if flag:
        cleaned_line=line.strip()
        parts=cleaned_line.split()
        word=parts[0]
        counts_str=parts[1]
        count=int(counts_str.replace('次',''))
        words.append(word)
        counts.append(count)
        if(len(counts)==5):
            break
plt.bar(words,counts)
plt.title("高频单词top5")
plt.xlabel("单词")
plt.ylabel("出现次数")
plt.savefig("top5.png")
