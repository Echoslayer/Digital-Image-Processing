---
title: 
draft: false
tags: 
date: 2024-09-16
---


## 機器視覺簡介及取像系統的選擇
## [課程及機器視覺簡介](https://www.youtube.com/watch?v=Hpp_wC0FMDE&list=PLI6pJZaOCtF0yLRQrV7JOBUaAfJ8Q-elm&index=1&pp=iAQB)
- ![[Pasted image 20240905191604.png]]

---
- ![[Pasted image 20240905191810.png]]

---
- 定義 
	- 以非接觸式的方式自動擷取影像·並經自動分析影像,從中抽取資料來控制一程序或動作 
- 需求 
	- 自動化大量生產+品質確認 人工檢測的問題(速度、可靠度、穩定度》 AOI的優勢(全自動、改進人工缺點)

---
- 定位(Positioning) 
	- 決定工件的位置及方向 
	- 光學點或工件本身的特徵 
	- 待測物相對於機台原點的位置 
	- 例:PCB(白色箭頭) >(x,y)及旋轉量:對角線兩點 
	- 自動對位精準且節省大量人力
- 識別(Recognition) 
	- 以物品本身的特徵判定身份 
		- 生物(Bio)特徵:臉孔、指紋、虹膜、聲音 
	- 工業應用:混料之零件(工件)識別與夾取/分流 
		- 幾何形狀、顏色紋理··
- 辨識(ldentification) 
	- 藉符號做物品身份判定 
		- Barcode,QRcode 
	- 包裝盒外的圖形或文字:辨識內容物 
	- 車牌辨識

---
- 瑕疵檢測(DefectDetection)
	- 工業上AOI之最大需求:可能需多站多次檢測 
	- 瑕疵:不想要、形狀大小未知、出現位置不定 
	- 瑕疵標準的訂定:漏檢(太鬆)或假警報(太嚴) 
	- 應用例 
		- 容器工業:瓶子之裂痕瑕疵及瓶內異物、碎片風險 >PCB、LOGO、TFT面板、木板坑洞··
- 驗證(Verification) 
	- 保證製程成功執行 
		- 自動化高速且自行運作監控 
		- 貼標:避免大量廢料(例:1200in之貼標籤機)
- 量測(Measurement)
	- 以影像進行尺寸的量測 
	- 例:各種工件的尺寸 線寬、圓的圓心與半徑、兩線距離

---
## [相機與鏡頭的搭配](https://www.youtube.com/watch?v=IeXPsNyjCNU&list=PLI6pJZaOCtF0yLRQrV7JOBUaAfJ8Q-elm&index=2&pp=iAQB)
- 相機與鏡頭搭配 
	- ![[Pasted image 20240905193203.png]]
	- 相同倍率 , 焦距越長光程越長
	- 有時拍攝物不能距離太近，就要換一顆f大一點的鏡頭

---

## [彩色成像品質的優化](https://www.youtube.com/watch?v=EgzT2La0E2k&list=PLI6pJZaOCtF0yLRQrV7JOBUaAfJ8Q-elm&index=8&pp=iAQB)
- 感光元件
	- 彩色
- ![[Pasted image 20240906130059.png]]

--- 
- ![[Pasted image 20240906130214.png]]

---
- ![[Pasted image 20240906130250.png]]
- 每個位置都會同時對應到
- RGB的感光元件
- 不需要額外交換顏色資訊
- 需要重複取像
- 可製作成大尺寸感光元件
- 成本高(壓電馬達)

---
- ![[Pasted image 20240906130543.png]]

---

## [檢測的基本概念](https://www.youtube.com/watch?v=TSJahiqB0yI&list=PLI6pJZaOCtF0yLRQrV7JOBUaAfJ8Q-elm&index=29&pp=iAQB)
- 自動化量測的需求
	- 檢測的基本概念
		- 自動化大量生產的尺寸量測與品質檢驗
			- 速度及量測精準度
			- 產品的微小化、精密化
			- 非接觸式量測~快速高精度
		- 傳統:投影放大儀、探針/游標卡尺接觸式
		- [Precision and accuracy in glacial geology](https://www.antarcticglaciers.org/glacial-geology/dating-glacial-sediments-2/precision-and-accuracy-glacial-geology/)
		- ![[Pasted image 20240909135059.png]]
		- ![[Pasted image 20240909135329.png]]
		- 由量測精密度的要求,找出相機所需之規格
		- 再依工作距離的限制,找出適當的鏡頭
## [直線擬合](https://www.youtube.com/watch?v=6Up66UJhj9o&list=PLI6pJZaOCtF0yLRQrV7JOBUaAfJ8Q-elm&index=30&pp=iAQB)
- 前言
	- 影像經過增強及尋邊後,得到一群代表物體邊界的資料點
	- 從這些離散的資料點,無法得知物體完整的輪廓線
	- 從這些資料點中,如何找出代表物體輪廓線的方程式:直線/曲線擬合
	- 由所得方程式可進行物件的量測(例:兩線間距離)
	- 大部份工業產品的外型曲線,都是由簡單的直線、圓弧及橢圓(曲線)所組成
- 最小平方法:最常使用的一種曲線逼近
	- 以一個簡單的函數來逼近一組資料點
	- 最小平方法所得到的曲線,並不會通過所有的資料點
	- 目標:資料點與所得到的曲線之間的誤差為最小
	- 最小平方法的缺點:
		- 一次只能找到一條線(由選定的點集合)
		- 容易受雜訊干擾影響準確度
- 直線擬合常用方法包括:
	- 線性迴歸(LinearRegression)
		- 較容易使用,計算時間較短
		- 缺點是容易受雜訊影響,而且一次只能
		- 處理一條直線
	- 霍氐轉換(HoughTransform)
		- 可找出所有直線,而且較不受雜訊影響
		- 缺點是運算時間長
## [霍氏轉換](https://www.youtube.com/watch?v=LSzOLydKhNI&list=PLI6pJZaOCtF0yLRQrV7JOBUaAfJ8Q-elm&index=31&pp=iAQB)
- 霍氏轉換
	- 霍氐轉換(Hough transform)是Hough在1962年所獲得的專利,用來偵測物體形狀的方法
	- 屬於一種使用投票機制決定參數值的參數估計法
	- 其作法是將影像平面內的每一個點,依序轉換至參數空間內進行處理
	- 利用轉換技術將影像平面內曲線偵測的問題,簡化成在參數空間內搜尋特徵點的問題
	- 假設在平面上有兩點,其座標分別為(x_i,y_i)與(x_j,y_j),通過這兩點的一條直線可以用一個截式直線方程式y=ax+b來表示·其中參數“代表斜率代表截距。接下來將方程式改寫成b=-ax+y 意即將直線從原先所在的影像空間(x-y平面) 轉換至參數空間內(a-b平面)。
	- ![[Pasted image 20240909140821.png]]
	- 利用上述特性,我們可以將參數空間以矩陣的方式分割成許多小格點,然後依序將影像空間內的每一個點代入參數空間內滿足上式的點不止一個，因此必需檢查b平面上的每一個點,如果滿足則將該點之累加計加1當影像空間內所有的資料點都代入後,接下來搜尋參數空間內具有最大累加值的點,該點的座標值即為最佳逼近直線的參數(m, c)
## [曲線擬合](https://www.youtube.com/watch?v=CX1sVWLNF8s&list=PLI6pJZaOCtF0yLRQrV7JOBUaAfJ8Q-elm&index=32&pp=iAQB)
- 圓及圓弧最小平方擬合法
- 三點定圓法
## [二維量測應用](https://www.youtube.com/watch?v=s81f-_roXFw&list=PLI6pJZaOCtF0yLRQrV7JOBUaAfJ8Q-elm&index=33&pp=iAQB)
- 二維影像尺寸量測
	- 在工廠生產的物件·出貨前常須要經過量測確定其尺寸,因此尺寸量測相當重要
	- 例:製作完成的電路板必須量測的尺度包括線寬、線距、焊墊的寬高及角度、光學點的大小與位置等，利用前面介紹的曲線擬合技術,即可用來測量線寬、線距、圓形焊墊、矩形焊墊、夾角等二維尺寸
- 線寬及線距的量測
	- 線寬或線距,都可以視為是兩條平行直線之間的距離,因此可以採用前述之霍氐轉換直線擬合法,來量測線寬及線距
	- 透過尋邊技術得到代表直線輪廓的邊界點後,將邊界點代入霍氐轉換直線擬合法,即可得到兩條直線方程式
	- 得到直線方程式後·就可以算出兩條平行線的距離
- 圓形焊墊的量測
	- 實務上須要量測的圓形物體相當多
		- 包括光學點、圓形焊墊、通孔、盲孔等。
	- 量測圓形物體尺寸的方法
		- 最小平方法、三點定圓法、修正式三點定圓法及霍氏轉換法
- 矩形焊墊之量測
	- 矩形焊墊的量測一樣可以採用霍氏轉換直線擬合法
	- 搜尋邊界點得到一組代表矩形焊墊輪廓的邊界點
	- 將邊界點代入霍氏轉換直線擬合法並尋找四條直線
	- 得到四條直線後·計算其交點得到矩形的四個邊角點算出矩形焊墊的寬度、高度、及相對於水平軸的旋轉角度
## [瑕疵檢測-參考比對法](https://www.youtube.com/watch?v=qWBNA8gnd3k&list=PLI6pJZaOCtF0yLRQrV7JOBUaAfJ8Q-elm&index=34&pp=iAQB)
- 何謂瑕疵檢測?
	- 瑕疵:不想要,未知形狀與尺寸,出現位置也不確定
	- 可能出現在產品上(任意位置)的缺陷有:形狀、尺寸、顏色、位置、表面傷痕等等,都可以被認定為瑕疵
	- 工業上對自動光學檢測的最大需求為瑕疵檢測
	- 品質管制人員之工作:借助他們的眼睛幫忙找出產品上各式各樣的瑕疵(辛苦且沒有成就感)
	- AOI come to help。
	- 判斷瑕疵的標準·事先必須詳細明確的規範清楚
	- 標準太嚴格會造成誤判(FP,falsepositive)·太寬鬆會造成漏檢(FN,falsenegative)
	- 根據檢測時是否參考到標準影像來分,瑕疵檢測技術可分成參考比對法與非參考比對法
- 參考比對法
	- 將待檢測影像與參考影像(金樣本)進行比對,因此參考比對法又稱為金樣本比對(goldentemplatematching/comparison,GTM/GTC)
	- 由於有標準影像可供比對,參考比對法的檢測原理相當簡單,只要是與標準影像不相同的地方,即可視為瑕疵
	- 優點:方法簡單且能完整地將所有缺點找出來
		- 效果要好,必須滿足定位準確及照明穩定的要求。
	- 根據標準影像的來源,參考比對法可進一步分成三種
		- Die-to-Die(D2D)
			- 將相鄰兩個圖案進行比對,找出兩者之間的差異,據以判斷是否為瑕疵
			- 適合用來檢測圖案具有重複出現特性之物體,例如光罩及晶圓的檢測
		- Die-to-Reference(D2R)
			- 將測試影像與事先攫取並存
			- 檔之標準影像進行比對·凡是與標準影像不一樣的地方即視為瑕疵
		- Die-to-Database(D2DB)
			- D2DB與D2R的比對方式類似,差別在於兩者的標準影像來源不同
			- D2DB之標準影像來源是原始設計資料檔,亦即標準影像甶電腦輔助設計資料庫所產生之圖形影像。
- 瑕疵檢測應用實例
	- ![[Pasted image 20240909144635.png]]
- 參考比對法的問題
	- ![[Pasted image 20240909144735.png]]
	- ![[Pasted image 20240909144805.png]]
## [影像對正](https://www.youtube.com/watch?v=bafv1pg_j68&list=PLI6pJZaOCtF0yLRQrV7JOBUaAfJ8Q-elm&index=35&pp=iAQB)
- 前言
	- XOR或影像相減(IS)檢測法·可以很容易的找出待測影像與金樣本影像之間的差異(瑕疵)
	- 但實務上很難讓待測物的與金樣本的位置一致,導致檢測的結果不如預期
	- 因此,在進行XOR/|S運算前必須找出待檢測影像與金樣本影像之間的空間差異,並將其修正回來，此過程即稱為影像對正(image registration)。
	- 影像對正的方法相當多,其中相關係數法特徵匹配法是最常見的兩種
	- 影像對正流程可概略劃分成以下四個步驟:
		- (1)選擇空間座標轉換
		- (2)特徵抽取與匹配
		- (3)計算空間座標轉換參數
		- (4)執行空間座標轉換
- 空間轉換模型
	- 剛體轉換
	- 仿射轉換
## [影像特徵分析](https://www.youtube.com/watch?v=yJWUyrZYc0g&list=PLI6pJZaOCtF0yLRQrV7JOBUaAfJ8Q-elm&index=36&pp=iAQB)
- 特徵種類可分成全域特徵、局部特徵、及關聯性特徵三大類
- 在樣本識別上,常用的特徵包括:位置、幾何形狀、色彩對比、及紋理等
	- 其中幾何形狀特徵的種類還包括:周長、面積、離心率、縱橫比、真圓度、粗糙度、長短距離比,…等。
	- 灰階影像之色階特徵包括:最大灰階值、最小灰階值、平均灰階值、灰階標準差等。
## [傳統分類技術](https://www.youtube.com/watch?v=mLsiXAKGF8g&list=PLI6pJZaOCtF0yLRQrV7JOBUaAfJ8Q-elm&index=37&pp=iAQB)
- 最鄰分類器 NN
- KNN
- 貝式分類器
## [非線性分類技術](https://www.youtube.com/watch?v=CqcSh_jKlZQ&list=PLI6pJZaOCtF0yLRQrV7JOBUaAfJ8Q-elm&index=38&pp=iAQB)
- SVM