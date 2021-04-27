# Snake

本專案透過製作貪食蛇的物件，建立蛇走的路徑模式：
1. 貪食蛇尊循下左右上的優先順序移動
2. 如果遵循下左右上的優先順序能吃得到食物，放出虛擬蛇，若虛擬蛇吃完食物還可以遵循下左右上的順序找到蛇尾，就讓蛇去吃
3. 若找不到食物及蛇尾，往離食物最遠的方向走
4. 若上述方式皆無法走，遵循下左右上的優先順序移動

## 實作：
1. 主蛇
  private:
    queue position:紀錄蛇目前的位置資訊
    tuple target:食物位置
    queue operations:若有能事先計算好可以走的路徑，紀錄在此
  
  public:
    queue nextPosition:回傳貪食蛇的下一步
      (1)若有事先計算好之operation，運行之
      (2)若operation皆運行完成，讓虛擬蛇去找到一條可以走的路，並運行之
      (3)若虛擬蛇未找到一條可以走的路，清空operation，計算離食物最遠的方向，往該方向走
      (4)若上述作業皆無法回傳下一步，遵循下左右上之優先順序移動
    tuple getTarget:在地圖中找到下一個食物目標位置
    bool collide:確認某個位置是否能行走
 
2. 虛擬蛇
  private:基本與主蛇相同
    queue position:紀錄蛇目前的位置資訊
    tuple target:食物位置

  public:
    queue nextPosition:回傳虛擬蛇的下一步位置
    bool collide:確認某個位置是否能行走
    queue nextPositionForTail:運用在尋找尾巴的計算
    queue nextPositionForRoad:運用在尋找食物的計算，並幫主蛇紀錄路徑
    queue getpositionNow:回傳目前虛擬蛇之位置
  
3. glbal function
  bool findingTail:運行虛擬蛇找到尾巴，回傳是否能找到尾巴
  bool findingRoad:運行虛擬蛇找到食物，並確定可以找到尾巴，回傳是否存在此路徑
 
