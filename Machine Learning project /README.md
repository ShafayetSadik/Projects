# Machine Learning-Driven Handover Optimization in LTE Networks

This project explores machine learning and reinforcement learning techniques for improving LTE handover decisions using real-world drive-test signal measurements. The work combines signal quality classification, supervised handover prediction, and Q-learning-based handover optimization to reduce unnecessary handovers while preserving network stability.

## Project Overview

Traditional LTE handover mechanisms often rely on fixed signal thresholds. In dynamic environments, this can cause delayed handovers, unnecessary handovers, or ping-pong effects. This project investigates a data-driven alternative using real LTE drive-test data collected in Dhaka, Bangladesh.

The project is divided into three main parts:

1. **Quality Signal Indicator (QSI) Analysis**
   - Classifies serving-cell signal quality into `Excellent`, `Good`, `Moderate`, and `Poor`.
   - Uses RSRP, RSRQ, and CINR/SNR-based composite scoring.
   - Compares manually derived QSI labels with unsupervised K-Means clustering.

2. **Handover Prediction**
   - Trains supervised classifiers to predict whether a handover should occur.
   - Handles class imbalance using undersampling, SMOTE, and Tomek Links.
   - Evaluates models using accuracy, precision, recall, F1-score, AUC, and confusion matrices.

3. **Handover Optimization**
   - Applies a hybrid Q-learning framework.
   - Uses classifier predictions as part of the exploration strategy.
   - Rewards beneficial handovers and penalizes unnecessary or poor-quality transitions.

## Dataset

The project is based on real-world LTE drive-test measurements. The primary dataset used in the notebooks is referenced as:

```text
Day2Data.csv
```

The dataset contains 647 samples and 11 columns:

| Column | Description |
| --- | --- |
| `Timestamp` | Measurement timestamp |
| `ServingCellID` | Current serving LTE cell ID |
| `PCellRSRP` | Serving cell RSRP |
| `PCellRSRQ` | Serving cell RSRQ |
| `NeighCellId` | Neighbor LTE cell ID |
| `NeighCellRSRP` | Neighbor cell RSRP |
| `NeighCellRSRQ` | Neighbor cell RSRQ |
| `Handover` | Binary target variable |
| `CINRvalue1` | CINR measurement component |
| `CINRvalue2` | CINR measurement component |
| `CINR` | Average/processed CINR value |

Class distribution:

| Class | Count |
| --- | ---: |
| Non-Handover | 553 |
| Handover | 94 |

> Note: The raw CSV files are not included in the current repository snapshot.


## Methods Used

### 1. QSI Classification

Serving-cell signal quality is evaluated using:

- RSRP
- RSRQ
- CINR/SNR

A weighted composite score is computed and mapped into four QSI categories. The best reported weighting was:

```text
RSRP = 0.5
RSRQ = 0.2
CINR/SNR = 0.3
```

QSI labels were then used for supervised model training and compared against K-Means clustering results after PCA-based dimensionality reduction.

### 2. Handover Prediction

The handover prediction task is treated as binary classification:

```text
0 = No Handover
1 = Handover
```

Models evaluated include:

- Logistic Regression
- Decision Tree
- Random Forest
- Support Vector Machine
- K-Nearest Neighbors
- Naive Bayes
- AdaBoost
- Gradient Boosting
- XGBoost
- CatBoost

Because the dataset is imbalanced, recall and F1-score are emphasized over accuracy alone.

### 3. Hybrid Q-Learning Optimization

The reinforcement learning stage defines:

- **State:** normalized signal measurements such as serving/neighbor RSRP, RSRQ, and CINR
- **Actions:** handover or no handover
- **Reward:** positive reward for stable high-quality decisions, penalty for unnecessary or poor handovers

The Q-learning agent learns a policy that reduces redundant handover decisions.

## Key Results

- Dataset size: 647 samples
- Original handover instances: 94 to 97, depending on notebook experiment
- Optimized handover count reported in the final Q-learning workflow: 71
- QSI classification accuracy reached approximately 99.23% in selected supervised experiments
- Logistic Regression with imbalance handling achieved strong handover recall, approximately 0.86 in the best reported run

The main outcome is that the hybrid ML and Q-learning framework reduced unnecessary handovers while maintaining signal-quality-aware decision-making.

## Requirements

```text
numpy
pandas
matplotlib
seaborn
scikit-learn
imbalanced-learn
xgboost
catboost
jupyter
```

Install them with:

```bash
pip install numpy pandas matplotlib seaborn scikit-learn imbalanced-learn xgboost catboost jupyter
```

## How to Run

1. Clone
2. Add the required dataset files to the project root:

```text
Day2Data.csv
Day2Data_with_QSI2.csv
Day2Data_with_ClustersPPP.csv
```

3. Start Jupyter Notebook:

```bash
jupyter notebook
```

4. Run the notebooks in this recommended order:

```text
Project of ML.ipynb
QSI_Take_2-01.ipynb
4709_project_HO_Pred_01.ipynb
QLearning2_01.ipynb
```

Some cells contain Google Colab paths such as `/content/Day2Data.csv`. Replace those with local paths before running locally.

## Limitations

- Some paths are environment-specific.
- The Q-learning environment uses a simplified transition model.
- The current feature set focuses mainly on signal metrics; future work can include latency, throughput, load, and user mobility context.

## Future Work
- Extend the Q-learning formulation with a richer state transition model.
- Explore deep reinforcement learning for larger and more dynamic state spaces.
- Incorporate additional network KPIs such as throughput, latency, packet loss, and cell load.

## License

No license file is currently included. Add a license before making the repository public if reuse or distribution is intended.
