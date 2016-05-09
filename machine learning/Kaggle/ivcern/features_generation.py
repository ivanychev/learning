import pandas as pd
import numpy as np

NA_VALUE = -999.0

# Binarising number of jets, which are narrow cones of hadrones produced after collision.
# PRI_jet_num   number of actual jets

def is_one_PRI_jet_num(df):
    df_new = df["PRI_jet_num"].apply(lambda x: 1 if x==1 else 0)
    df_new.name = "one_PRI_jet_num"
    return df_new

def are_two_PRI_jet_num(df):
    df_new = df["PRI_jet_num"].apply(lambda x: 1 if x==2 else 0)
    df_new.name = "two_PRI_jet_num"
    return df_new

def are_three_PRI_jet_num(df):
    df_new = df["PRI_jet_num"].apply(lambda x: 1 if x==3 else 0)
    df_new.name = "three_PRI_jet_num"
    return df_new

def are_multi_PRI_jet_num(df):
    df_new = df["PRI_jet_num"].apply(lambda x: 1 if x>3 else 0)
    df_new.name = "multi_PRI_jet_num"
    return df_new

funcs_jet_num = [is_one_PRI_jet_num, are_two_PRI_jet_num, are_three_PRI_jet_num, are_multi_PRI_jet_num]

# Processing [-pi, pi] angles
_ANGLES = ["DER_met_phi_centrality", "PRI_tau_eta", "PRI_tau_phi", "PRI_lep_eta", "PRI_lep_phi", "PRI_met_phi",
           "PRI_jet_subleading_eta", "PRI_jet_subleading_phi"]

def abs_feature(df, col_name, postfix = "_abs"):
    df_new = df[col_name].apply(lambda x: np.abs(x))
    mask = df[col_name] == NA_VALUE
    df_new[mask] = NA_VALUE
    df_new.name = col_name + postfix
    return df_new

def DER_met_phi_centrality_abs(df):
    return abs_feature(df, "DER_met_phi_centrality")

def PRI_tau_eta_abs(df):
    return abs_feature(df, "PRI_tau_eta")

def PRI_tau_phi_abs(df):
    return abs_feature(df, "PRI_tau_phi")

def PRI_lep_eta_abs(df):
    return abs_feature(df, "PRI_lep_eta")

def PRI_lep_phi_abs(df):
    return abs_feature(df, "PRI_lep_phi")

def PRI_met_phi_abs(df):
    return abs_feature(df, "PRI_met_phi")

def PRI_jet_subleading_eta_abs(df):
    return abs_feature(df, "PRI_jet_subleading_eta")

def PRI_jet_subleading_phi_abs(df):
    return abs_feature(df, "PRI_jet_subleading_phi")

funcs_angle_abs = [DER_met_phi_centrality_abs,
                   PRI_tau_eta_abs,
                   PRI_tau_phi_abs,
                   PRI_lep_eta_abs,
                   PRI_lep_phi_abs,
                   PRI_met_phi_abs,
                   PRI_jet_subleading_eta_abs,
                   PRI_jet_subleading_phi_abs]

# Cartesian coordinates of each momentum might be useful
def _p_projection(df_pt, df_eta, df_phi, callabl):
    df_new = callabl(df_pt, df_eta, df_phi)
    mask = df_pt < 0
    df_new[mask] = NA_VALUE
    return df_new

def _px(df_pt, df_eta, df_phi):
    return _p_projection(df_pt, df_eta, df_phi, lambda pt, eta, phi: pt * np.cos(phi))

def _py(df_pt, df_eta, df_phi):
    return _p_projection(df_pt, df_eta, df_phi, lambda pt, eta, phi: pt * np.sin(phi))

def _pz(df_pt, df_eta, df_phi):
    return _p_projection(df_pt, df_eta, df_phi, lambda pt, eta, phi: pt * np.sinh(eta))

def _get_cartesian_momentums(df, prefix):
    df_pt = df[prefix + "_pt"]
    df_eta = df[prefix + "_eta"]
    df_phi = df[prefix + "_phi"]

    new_x = _px(df_pt, df_eta, df_phi)
    new_y = _py(df_pt, df_eta, df_phi)
    new_z = _pz(df_pt, df_eta, df_phi)
    new_abs_x = new_x.apply(lambda x: np.abs(x))
    new_abs_y = new_y.apply(lambda x: np.abs(x))
    new_abs_z = new_z.apply(lambda x: np.abs(x))
    new_norm = np.sqrt(new_x ** 2 + new_y ** 2 + new_z ** 2)
    new_df = pd.DataFrame({prefix + "_x": new_x,
                           prefix + "_y": new_y,
                           prefix + "_z": new_z,
                           prefix + "_x_abs": new_abs_x,
                           prefix + "_y_abs": new_abs_y,
                           prefix + "_z_abs": new_abs_z,
                           prefix + "_norm": new_norm})
    mask = df_pt < 0
    new_df[mask] = NA_VALUE
    return new_df

def PRI_jet_leading_cart(df):
    return _get_cartesian_momentums(df, "PRI_jet_leading")

def PRI_jet_subleading_cart(df):
    return _get_cartesian_momentums(df, "PRI_jet_subleading")

def PRI_tau_cart(df):
    return _get_cartesian_momentums(df, "PRI_tau")

def PRI_lep_cart(df):
    return _get_cartesian_momentums(df, "PRI_lep")

funcs_momentum_features = [PRI_jet_leading_cart, PRI_jet_subleading_cart, PRI_tau_cart, PRI_lep_cart]

# Leading and subleading jets eta angles difference. The feature is how far two etas from being different.
# We interpret is as dictance from point (eta1, eta2) to eta1=eta2 line

def _l2_norm(x, y):
    return np.sqrt(x**2 + y**2)
def _equality_distance(x, y):
    return np.sqrt((x**2) / 2 + (y**2) / 2 - x*y)

def jet_eta_corr(df):
    new_df = pd.Series(_equality_distance(df["PRI_jet_leading_eta"], df["PRI_jet_subleading_eta"]))
    new_df.name = "PRI_jet_eta_distance"
    mask = df['PRI_jet_num'] < 2
    new_df[mask] = NA_VALUE
    return new_df

def lep_tau_corr(df):
    x = df['PRI_lep_eta']
    y = df['PRI_tau_eta']
    new_df = _equality_distance(x, y)
    new_df.name = 'lep_tau_corr'
    return new_df


def lep_jet_corr(df):
    x = df['PRI_lep_eta']
    y = df['PRI_jet_leading_eta']
    new_df = _equality_distance(x, y)
    new_df.name = 'lep_jet_corr'
    return new_df


def tau_jet_corr(df):
    x = df['PRI_tau_eta']
    y = df['PRI_jet_leading_eta']
    new_df = _equality_distance(x, y)
    new_df.name = 'tau_jet_corr'
    return new_df

def particle_xy_norm(df, particle_prefix1, particle_prefix2):
    x = df[particle_prefix1 + '_x'] + df[particle_prefix2 + '_x']
    y = df[particle_prefix1 + '_y'] + df[particle_prefix2 + '_y']
    new_df = _l2_norm(x,y)
    new_df.name = particle_prefix1 + '_' + particle_prefix2 + "_corr"
    return new_df

def tau_jet_xy_corr(df):
    new_df =  particle_xy_norm(df, 'PRI_tau', 'PRI_jet_leading')
    new_df[df['PRI_jet_num']==0] = NA_VALUE
    return new_df

def lep_jet_xy_corr(df):
    new_df = particle_xy_norm(df, 'PRI_lep', 'PRI_jet_leading')
    new_df[df['PRI_jet_num']==0] = NA_VALUE
    return new_df

def tau_lep_xy_corr(df):
    return particle_xy_norm(df, 'PRI_lep', 'PRI_tau')

funcs_eta = [jet_eta_corr, tau_jet_xy_corr, lep_jet_xy_corr, tau_lep_xy_corr, lep_tau_corr, lep_jet_corr, tau_jet_corr]

# Different addition features



new_features_funcs = funcs_angle_abs + funcs_momentum_features + funcs_eta # + funcs_jet_num