# 建议添加参数检查,确保 $1 不为空
if [ -z "$1" ]; then
    echo "Error: Please provide a model name as argument"
    exit 1
fi

save_name="/home/mjwei/download_models/$1"
# save_name="${save_dir}/$(echo "$1" | cut -d'/' -f2)"
hf_dataset_or_model="$1"
# export HUGGINGFACE_TOKEN=your_access_token
echo $save_name
echo $hf_dataset_or_model
export HF_ENDPOINT=https://hf-mirror.com

# export HF_HUB_ENABLE_HF_TRANSFER=1
# 定义下载函数 repo-type = dataset or space
download_dataset() {
    # huggingface-cli download --token $your_access_token --repo-type dataset --resume-download $hf_dataset_or_model --local-dir $save_name --force-download  --include data/val-00001-of-00002.parquet
    huggingface-cli download --repo-type model --resume-download $hf_dataset_or_model --local-dir $save_name --force-download
}

# 循环下载，直到下载成功为止
while true; do
    download_dataset  # 调用下载函数
    return_code=$?   # 获取命令的返回码

    if [ $return_code -eq 0 ]; then
        echo "Download successful."
        break  # 下载成功时退出循环
    else
        echo "Download failed. Retrying in 10 seconds..."
        sleep 10  # 下载失败时等待 10 秒后重试
    fi
done