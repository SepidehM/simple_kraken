from Bio import SeqIO

name_file = ["/home/sepideh/Desktop/DB/jf/GCF_000006625.1_ASM662v1_genomic.fna",
             "/home/sepideh/Desktop/DB/genome/GCF_000009685.1_ASM968v1_genomic.fna",
             "/home/sepideh/Desktop/DB/jf/GCF_000169895.1_ASM16989v1_genomic.fna",
             "/home/sepideh/Desktop/DB/jf/GCF_000762315.1_ASM76231v1_genomic.fna",
            ]
with open("/home/sepideh/Desktop/DB/query2.fastq", "w") as fastq:
    for name in name_file:
        with open(name, "r") as fasta:
            for record in SeqIO.parse(fasta, "fasta"):
                record.seq = record.seq[:200]

            record.letter_annotations["phred_quality"] = [40]*len(record)
            SeqIO.write(record, fastq, "fastq")